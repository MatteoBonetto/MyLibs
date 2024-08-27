#ifndef DBSCAN_H
#define DBSCAN_H

#include <Eigen/Dense>
#include <vector>
#include <cmath>

using namespace Eigen;

typedef MatrixXd MatrixType;
typedef VectorXd VectorType;

class DBSCAN {
public:
    DBSCAN(double epsilon, int minPts);

    void fit(const MatrixType& points);

    VectorXi getLabels() const;

private:
    double epsilon;
    int minPts;
    VectorXi labels;

    double distance(const VectorType& a, const VectorType& b);

    std::vector<int> regionQuery(const MatrixType& points, int index);

    void expandCluster(const MatrixType& points, int index, std::vector<int>& neighbors, int clusterId);
};

#endif
