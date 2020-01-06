#include <cmath>
#include "EdgeGraph.hpp"
#include "MST.hpp"
#include "AdjacencyGraph.hpp"
#include "MSTSolver.hpp"

template <class TVertex, class TCoordinate, class TDistance>
TDistance MSTSolver<TVertex, TCoordinate, TDistance>::getDistance() const
{
    return distance;
}

template <class TVertex, class TCoordinate, class TDistance>
MSTSolver<TVertex, TCoordinate, TDistance>::MSTSolver(std::vector<std::pair<TCoordinate, TCoordinate>>& points)
{
    distance = 0;
    EdgeGraph<TVertex, TDistance> graph(points.size());
    for(int i = 0; i < points.size(); ++i)
    {
        for(int j = 0; j < points.size(); ++j)
        {
            if(i == j)
            {
                continue;
            }
            graph.add(i, j, std::hypot(points[i].first - points[j].first, points[i].second - points[j].second));
        }
    }

    MST MST(graph);
    AdjacencyGraph<TVertex, TDistance> tree(MST.getTree());
    std::vector<TVertex> path = tree.dfs(0);
    path.push_back(path[0]);
    for(int i = 0; i < path.size() - 1; ++i)
    {
        distance += hypot(points[path[i]].first - points[path[i + 1]].first, points[path[i]].second - points[path[i + 1]].second);
    }
}

template class MSTSolver<int, double, double>;