#include <cmath>
#include "EdgeGraph.hpp"

Edge::Edge(): from(0), to(0), weight(INFINITY) {};

Edge::Edge(int from, int to, double weight): from(from), to(to), weight(weight) {};

EdgeGraph::EdgeGraph() = default;

EdgeGraph::EdgeGraph(int size)
{
    graph_size = size;
}

EdgeGraph::EdgeGraph(const EdgeGraph* from): EdgeGraph(from->size())
{
    this->edges = from->edges;
}

void EdgeGraph::add(int from, int to, double weight)
{
    edges.emplace_back(Edge(from, to, weight));
}

int EdgeGraph::edgesNum() const
{
    return edges.size();
}

int EdgeGraph::size() const
{
    return graph_size;
}

std::vector<Edge>::const_iterator EdgeGraph::begin() const
{
    return edges.cbegin();
}

std::vector<Edge>::const_iterator EdgeGraph::end() const
{
    return edges.cend();
}