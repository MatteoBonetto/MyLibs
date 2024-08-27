#include "Statistic.h"

double mean(const Eigen::VectorXd& data) {
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    return sum / data.size();
}

// Function to calculate the median of a vector
double median(const Eigen::VectorXd& vec) {
    std::vector<double> data(vec.data(), vec.data() + vec.size());
    std::sort(data.begin(), data.end());
    size_t size = data.size();
    if (size % 2 == 0 && size != 0) {
        return (data[(size_t) ((float)(size) / 2.0 - 1)] + data[(size_t) ((float)(size) / 2.0)]) / 2.0;
    } else if(size % 2 != 0){
        return data[(size_t) (size / 2)];
    } else {
        std::cerr << "Error - median with an empty vector" << std::endl;
        exit(EXIT_FAILURE);
    }
}

// Function to calculate the Median Absolute Deviation (MAD)
double mad(const Eigen::VectorXd& data) {
    double med = median(data);
    Eigen::VectorXd abs_devs = (data.array() - med).cwiseAbs();
    return median(abs_devs);
}