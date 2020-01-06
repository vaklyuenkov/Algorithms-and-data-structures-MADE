#include "MST.hpp"
#include "NotOverlappingSets.hpp"

template <class TVertex, class TWeight>
EdgeGraph<TVertex, TWeight> MST<TVertex, TWeight>::getTree() const
{
    return tree;
}

template <class TVertex, class TWeight>
MST<TVertex, TWeight>::MST(EdgeGraph<TVertex, TWeight>& graph)
{
    tree = EdgeGraph<TVertex, TWeight>(graph.size());
    NotOverlappingSets<TVertex> set(graph.size());

    while(tree.edgesNum() < 2 * (graph.size() - 1))
    {
        std::vector<Edge<TVertex, TWeight>> cheapestEdges(graph.size(), Edge<TVertex, TWeight>());
        for(auto edge: graph)
        {
            if(set.find(edge.from) == set.find(edge.to))
            {
                continue;
            }
            if(edge.weight < cheapestEdges[set.find(edge.to)].weight)
            {
                cheapestEdges[set.find(edge.to)] = Edge(edge.from, edge.to, edge.weight);
            }
            if(edge.weight < cheapestEdges[set.find(edge.from)].weight)
            {
                cheapestEdges[set.find(edge.from)] = Edge(edge.from, edge.to, edge.weight);
            }
        }

        for(auto edge: cheapestEdges)
        {
            if(set.find(edge.from) != set.find(edge.to))
            {
                tree.add(edge.from, edge.to, edge.weight);
                tree.add(edge.to, edge.from, edge.weight);
                set.unionSets(edge.from, edge.to);
            }
        }
    }
}

template class MST<int, double>;