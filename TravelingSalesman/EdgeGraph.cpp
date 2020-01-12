#include <cmath>
#include "EdgeGraph.hpp"


template <class TVertex, class TWeight>
Edge<TVertex, TWeight>::Edge(): from(0), to(0), weight(INFINITY) {};

template <class TVertex, class TWeight>
Edge<TVertex, TWeight>::Edge(TVertex from, TVertex to, TWeight weight): from(from), to(to), weight(weight) {};

template <class TVertex, class TWeight>
EdgeGraph<TVertex, TWeight>::EdgeGraph() = default;

template <class TVertex, class TWeight>
EdgeGraph<TVertex, TWeight>::EdgeGraph(int size)
{
    graph_size = size;
}

template <class TVertex, class TWeight>
EdgeGraph<TVertex, TWeight>::EdgeGraph(const EdgeGraph* from): EdgeGraph(from->size())
{
    this->edges = from->edges;
}

template <class TVertex, class TWeight>
void EdgeGraph<TVertex, TWeight>::add(TVertex from, TVertex to, TWeight weight)
{
    edges.emplace_back(Edge(from, to, weight));
}

template <class TVertex, class TWeight>
int EdgeGraph<TVertex, TWeight>::edgesNum() const
{
    return edges.size();
}

template <class TVertex, class TWeight>
int EdgeGraph<TVertex, TWeight>::size() const
{
    return graph_size;
}

template <class TVertex, class TWeight>
typename std::vector<Edge<TVertex, TWeight>>::const_iterator EdgeGraph<TVertex, TWeight>::begin() const
{
    return edges.cbegin();
}

template <class TVertex, class TWeight>
typename std::vector<Edge<TVertex, TWeight>>::const_iterator EdgeGraph<TVertex, TWeight>::end() const
{
    return edges.cend();
}

template class EdgeGraph<int, double>;
template class Edge<int, double>;