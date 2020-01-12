#include <cmath>
#include "BruteForceSolver.hpp"

template <class TVertex, class TCoordinate, class TDistance>
BruteForceSolver<TVertex, TCoordinate, TDistance>::BruteForceSolver(std::vector<std::pair<TCoordinate, TCoordinate>>& points)
{
    distance = INFINITY;
    std::vector<bool> used(points.size(), false);
    std::vector<int> path = {};
    generatePath(points, used, path);
}

template <class TVertex, class TCoordinate, class TDistance>
void BruteForceSolver<TVertex, TCoordinate, TDistance>::generatePath(std::vector<std::pair<TCoordinate, TCoordinate>>& points, std::vector<bool>& used, std::vector<TVertex>& path)
{
    bool flag = false;
    for(int i = 0; i < used.size(); ++i)
    {
        if(!used[i])
        {
            flag = true;
            used[i] = true;
            path.push_back(i);
            generatePath(points, used, path);
            path.pop_back();
            used[i] = false;
        }
    }
    if(!flag)
    {
        distance = std::min(computeDistance(points, path), distance);
    }
}

template <class TVertex, class TCoordinate, class TDistance>
TDistance BruteForceSolver<TVertex, TCoordinate, TDistance>::computeDistance(std::vector<std::pair<TCoordinate, TCoordinate>>& points, std::vector<TVertex>& path) const
{
    double currentDistance = 0;
    path.push_back(path[0]);
    for(int i = 0; i < path.size() - 1; ++i)
    {
        currentDistance += hypot(points[path[i]].first - points[path[i + 1]].first, points[path[i]].second - points[path[i + 1]].second);
    }
    path.pop_back();
    return currentDistance;
}

template <class TVertex, class TCoordinate, class TDistance>
TDistance BruteForceSolver<TVertex, TCoordinate, TDistance>::getDistance() const
{
    return distance;
}

template class BruteForceSolver <int, double, double>;