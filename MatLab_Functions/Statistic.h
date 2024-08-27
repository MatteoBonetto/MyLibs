#ifndef STATISTIC_H
#define STATISTIC_H
#include <iostream>
#include <vector>
#include <numeric> // For std::accumulate
#include <algorithm> // For std::sort and std::nth_element
#define EIGEN_USE_MKL_ALL
#define EIGEN_USE_BLAS
#define EIGEN_USE_LAPACKE
#include <Eigen/Dense>

double mean(const Eigen::VectorXd& data);

double median(const Eigen::VectorXd& vec);

double mad(const Eigen::VectorXd& data);

#endif