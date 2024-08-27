#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <cmath>
#include <chrono>
#include "IRLS.h"
#include "Statistic.h"

using namespace Eigen;
using namespace std;

// Funzione per calcolare i pesi robusti (utilizziamo il metodo di Huber)
VectorXd calculateWeights_Huber(const VectorXd &residuals, const VectorXd& h) {

    VectorXd weights(residuals.size());
    double s = mad(residuals) / 0.6745;
    double k = 1.345;

    for (int i = 0; i < residuals.size(); ++i) {
        
        double abs_res = fabs(residuals[i]);
        double r = abs_res / (k * s * std::sqrt(fabs(1 - h(i))));
        if (r <= 1) {
            weights[i] = 1;
        } else {
            weights[i] = 1 / fabs(r);
        }

    }
    return weights;
}

// Funzione per eseguire la regressione lineare ponderata
VectorXd weightedLeastSquares(const MatrixXd &X, const VectorXd &y, const VectorXd &weights) {
    MatrixXd W = weights.asDiagonal();
    MatrixXd XTWX = X.transpose() * W * X;
    VectorXd XTWy = X.transpose() * W * y;
    if ((XTWX).determinant() == 0){
        std::cout << "Matrix not invertible" << std::endl;
        exit(EXIT_FAILURE);
    }
    return XTWX.ldlt().solve(XTWy);
}

// Function for robust regression using IRLS
VectorXd robustfit(const VectorXd &x, const VectorXd &y, int max_iters, double tol) {
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
    if (((y * y.transpose()).inverse()).determinant() == 0){
        std::cout << "Matrix not invertible" << std::endl;
        exit(EXIT_FAILURE);
    }
    MatrixXd pseudo_y = y.transpose() * (weights.asDiagonal() * y * y.transpose()).inverse();

    for (int iter = 0; iter < max_iters; ++iter) {
        MatrixXd H = weights.asDiagonal() * X * beta * pseudo_y;
        leverage = H.diagonal();
        y_pred = X * beta;
        residuals = y - y_pred;
        // Update weights using Huber method with leverage
        weights = calculateWeights_Huber(residuals, leverage);
        // Update beta using weighted least squares
        beta_new = weightedLeastSquares(X, y, weights);
        // Check for convergence
        if ((beta_new - beta).norm() < tol) {
            return beta_new;
        }
        // Update beta for the next iteration
        beta = beta_new;
    }

    // Return the final estimated coefficients
    return beta;
}