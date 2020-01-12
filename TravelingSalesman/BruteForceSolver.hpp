#pragma once

#include <vector>
#include <utility>

template <class TVertex, class TCoordinate, class TDistance>
class BruteForceSolver {
public:
    explicit BruteForceSolver(std::vector<std::pair<TCoordinate, TCoordinate>>& points);
    ~BruteForceSolver() = default;
    BruteForceSolver(const BruteForceSolver&) = delete; // according to five-rule
    BruteForceSolver(BruteForceSolver&&) = delete;
    BruteForceSolver& operator=(const BruteForceSolver&) = delete;
    BruteForceSolver& operator=(BruteForceSolver&&) = delete;


    TDistance getDistance() const;
private:
    void generatePath(std::vector<std::pair<TCoordinate, TCoordinate>>& points, std::vector<bool>& used, std::vector<TVertex>& path);
    TDistance computeDistance(std::vector<std::pair<TCoordinate, TCoordinate>>& points, std::vector<TVertex>& path) const;
    TDistance distance;
};