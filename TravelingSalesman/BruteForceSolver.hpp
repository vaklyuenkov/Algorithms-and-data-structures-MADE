#pragma once

#include <vector>
#include <utility>

class BruteForceSolver {
public:
    explicit BruteForceSolver(std::vector<std::pair<double, double>>& points);
    ~BruteForceSolver() = default;
    BruteForceSolver(const BruteForceSolver&) = delete; // according to five-rule
    BruteForceSolver(BruteForceSolver&&) = delete;
    BruteForceSolver& operator=(const BruteForceSolver&) = delete;
    BruteForceSolver& operator=(BruteForceSolver&&) = delete;


    double getDistance() const;
private:
    void generatePath(std::vector<std::pair<double, double>>& points, std::vector<bool>& used, std::vector<int>& path);
    double computeDistance(std::vector<std::pair<double, double>>& points, std::vector<int>& path) const;
    double distance;
};