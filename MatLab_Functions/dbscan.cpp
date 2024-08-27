#include "dbscan.h"

DBSCAN::DBSCAN(double epsilon, int minPts) : epsilon(epsilon), minPts(minPts) {}

void DBSCAN::fit(const MatrixType& points) {
    int n = points.rows();
    labels = VectorXi::Constant(n, -1); // -1 means unvisited/noise
    int clusterId = 0;

    for (int i = 0; i < n; ++i) {
        if (labels(i) != -1) continue; // Already visited

        std::vector<int> neighbors = regionQuery(points, i);
        if (neighbors.size() < minPts) {
            labels(i) = -2; // Mark as noise
        }
        else {
            expandCluster(points, i, neighbors, clusterId);
            clusterId++;
        }
    }
}

VectorXi DBSCAN::getLabels() const { return labels; }


double DBSCAN::distance(const VectorType& a, const VectorType& b) {
    return (a - b).norm();
}

std::vector<int> DBSCAN::regionQuery(const MatrixType& points, int index) {
    std::vector<int> neighbors;
    VectorType point = points.row(index);
    for (int i = 0; i < points.rows(); ++i) {
        if (distance(point, points.row(i)) <= epsilon) {
            neighbors.push_back(i);
        }
    }
    return neighbors;
}

void DBSCAN::expandCluster(const MatrixType& points, int index, std::vector<int>& neighbors, int clusterId) {
    labels(index) = clusterId;

    std::vector<int> seedSet = neighbors;
    for (size_t i = 0; i < seedSet.size(); ++i) {
        int currIdx = seedSet[i];
        if (labels(currIdx) == -2) {
            labels(currIdx) = clusterId; // Change noise to cluster
        }
        if (labels(currIdx) != -1) continue;

        labels(currIdx) = clusterId;
        std::vector<int> newNeighbors = regionQuery(points, currIdx);
        if (newNeighbors.size() >= minPts) {
            seedSet.insert(seedSet.end(), newNeighbors.begin(), newNeighbors.end());
        }
    }
}