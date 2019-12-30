#include <cmath>
#include "BruteForceSolver.hpp"

BruteForceSolver::BruteForceSolver(std::vector<std::pair<double, double>>& points)
{
    distance = INFINITY;
    std::vector<bool> used(points.size(), false);
    std::vector<int> path = {};
    generatePath(points, used, path);
}

void BruteForceSolver::generatePath(std::vector<std::pair<double, double>>& points, std::vector<bool>& used, std::vector<int>& path)
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

double BruteForceSolver::computeDistance(std::vector<std::pair<double, double>>& points, std::vector<int>& path) const
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
double BruteForceSolver::getDistance() const
{
    return distance;
}