
#include "IRLS.h"
#include "Statistic.h"
#include <thread>
#include <sstream>
#include<fstream>

using namespace Eigen;
using namespace std;




// Function to compute the leverage values dynamically
void computeLeverage(const MatrixXd& X, const VectorXd& weights, VectorXd& leverage) {
    MatrixXd W = weights.asDiagonal();
    MatrixXd Xt = X.transpose();
    MatrixXd XtWX = (Xt * W * X);
    Eigen::HouseholderQR<Eigen::MatrixXd> qr(XtWX);
    // Calcolo dell'inversa di XtWX utilizzando la decomposizione QR
    Eigen::MatrixXd XtWX_inv = qr.solve(Eigen::MatrixXd::Identity(XtWX.rows(), XtWX.cols()));
    //MatrixXd XtWX_inv = (Xt * W * X).ldlt().solve(MatrixXd::Identity(2, 2));
    MatrixXd H = X * XtWX_inv * Xt * W;
    leverage = H.diagonal();
}

// Funzione per calcolare i pesi robusti (utilizziamo il metodo di Huber)
VectorXd calculateWeights_Huber(const VectorXd &residuals, const VectorXd& h) {
    VectorXd weights(residuals.size());
    double s = mad(residuals) / 0.6745;
    double k = 1.345;

    for (int i = 0; i < residuals.size(); ++i) {
        double abs_res = fabs(residuals[i]);
        double r = abs_res / (k * s * std::sqrt(1 - h(i)));
        if (r <= 1) {
            weights[i] = 1;
        } else {
            weights[i] = 1 / fabs(r);
        }
    }
    return weights;
}

// Funzione per calcolare i pesi robusti
VectorXd calculateWeights_Fast(const VectorXd &residuals, const double& th) {
    VectorXd weights(residuals.size());

    for (int i = 0; i < residuals.size(); ++i) {
        double abs_res = std::abs(residuals[i]);
        if (abs_res <= th) {
            weights[i] = 1;
        } else {
            weights[i] = 0;
        }
    }
    return weights;
}

// Funzione per eseguire la regressione lineare ponderata
VectorXd weightedLeastSquares(const MatrixXd &X, const VectorXd &y, const VectorXd &weights) {
    MatrixXd W = weights.asDiagonal();
    MatrixXd XTWX = X.transpose() * W * X;
    VectorXd XTWy = X.transpose() * W * y;
    return XTWX.ldlt().solve(XTWy);
    //return y;
    //return XTWX.inverse() * XTWy;
}

// Function for robust regression using IRLS
VectorXd robustfit(const VectorXd &x, const VectorXd &y, int max_iters, double tol, std::string method) {
    /*
    auto t0 = std::chrono::high_resolution_clock::now();
    // Open the file
    std::stringstream ss;
    ss << std::this_thread::get_id();
    std::string filename = ss.str() + ".txt";
    std::ofstream file(filename, ios::app);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit;
    }
    file << "t0,\t\t\t tf,\t\t\t dt,\t\t\t points" << std::endl << t0.time_since_epoch();
    */
    MatrixXd X(x.size(), 2);
    X.col(0).setOnes();
    X.col(1) = x;

    int n = X.rows();
    VectorXd leverage(n);
    VectorXd residuals(n);
    VectorXd y_pred(n);
    VectorXd weights = VectorXd::Ones(n);
    // Initial beta estimate using ordinary least squares
    VectorXd beta = weightedLeastSquares(X, y, weights);
    VectorXd beta_new = beta;

    for (int iter = 0; iter < max_iters; ++iter) {
        if(method == "Huber")
            computeLeverage(X, weights, leverage);
        // Compute predicted values
        y_pred = X * beta;
        // Compute residuals
        residuals = y - y_pred;
        // Update weights using Huber method with leverage
        if(method == "Huber"){
            weights = calculateWeights_Huber(residuals, leverage);
        }else if(method == "Fast"){
            weights = calculateWeights_Fast(residuals);
        }
        // Update beta using weighted least squares
        beta_new = weightedLeastSquares(X, y, weights);
        // Check for convergence
        if ((beta_new - beta).norm() < tol) {
            beta = beta_new;
            break;
        }
        // Update beta for the next iteration
        beta = beta_new;
    }
    //auto tf = std::chrono::high_resolution_clock::now();
    //file << ",\t " << tf.time_since_epoch() << ",\t " << (tf - t0).count() << ",\t\t " << n << std::endl;
    
    return beta;
}