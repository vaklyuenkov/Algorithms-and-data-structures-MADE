#include "MST.hpp"
#include "NotOverlappingSets.hpp"

EdgeGraph MST::getTree() const
{
    return tree;
}

MST::MST(EdgeGraph& graph)
{
    tree = EdgeGraph(graph.size());
    NotOverlappingSets set(graph.size());

    while(tree.edgesNum() < 2 * (graph.size() - 1))
    {
        std::vector<Edge> cheapestEdges(graph.size(), Edge());
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
