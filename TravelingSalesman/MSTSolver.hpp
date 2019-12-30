#pragma once

#include <vector>
#include <utility>

class MSTSolver {
public:
    explicit MSTSolver(std::vector<std::pair<double, double>>& points);
    ~MSTSolver() = default;
    MSTSolver(const MSTSolver&) = delete; // according to five-rule
    MSTSolver(MSTSolver&&) = delete;
    MSTSolver& operator=(const MSTSolver&) = delete;
    MSTSolver& operator=(MSTSolver&&) = delete;

    double getDistance() const;

private:
    double distance;
};