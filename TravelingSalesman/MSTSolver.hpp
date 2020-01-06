#pragma once

#include <vector>
#include <utility>

template <class TVertex, class TCoordinate, class TDistance>
class MSTSolver {
public:
    explicit MSTSolver(std::vector<std::pair<TCoordinate, TCoordinate>>& points);
    ~MSTSolver() = default;
    MSTSolver(const MSTSolver&) = delete; // according to five-rule
    MSTSolver(MSTSolver&&) = delete;
    MSTSolver& operator=(const MSTSolver&) = delete;
    MSTSolver& operator=(MSTSolver&&) = delete;

    TDistance getDistance() const;

private:
    TDistance distance;
};