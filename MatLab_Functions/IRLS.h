#ifndef IRLS_H
#define IRLS_H
#define EIGEN_USE_MKL_ALL
#define EIGEN_USE_BLAS
#define EIGEN_USE_LAPACKE
#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <cmath>
#include <chrono>

using namespace Eigen;
using namespace std;

VectorXd robustfit(const VectorXd &x, const VectorXd &y, int max_iters = 50, double tol = 1e-6, std::string method = "Huber");

VectorXd calculateWeights_Huber(const VectorXd &residuals, const VectorXd& h);

VectorXd weightedLeastSquares(const MatrixXd &X, const VectorXd &y, const VectorXd &weights);

void computeLeverage(const MatrixXd& X, const VectorXd& weights, VectorXd& leverage);

VectorXd calculateWeights_Fast(const VectorXd &residuals, const double& th = 0.03);

#endif