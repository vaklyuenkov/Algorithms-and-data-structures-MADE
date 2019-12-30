#include <cmath>
#include "EdgeGraph.hpp"
#include "MST.hpp"
#include "AdjacencyGraph.hpp"
#include "MSTSolver.hpp"

double MSTSolver::getDistance() const
{
    return distance;
}

MSTSolver::MSTSolver(std::vector<std::pair<double, double>>& points)
{
    distance = 0;
    EdgeGraph graph(points.size());
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
    AdjacencyGraph tree(MST.getTree());
    std::vector<int> path = tree.dfs(0);
    path.push_back(path[0]);
    for(int i = 0; i < path.size() - 1; ++i)
    {
        distance += hypot(points[path[i]].first - points[path[i + 1]].first, points[path[i]].second - points[path[i + 1]].second);
    }
}

