#pragma once

#include <vector>
#include <utility>
#include "EdgeGraph.hpp"

template <class TVertex, class TWeight>
class AdjacencyGraph {
public:
    AdjacencyGraph();
    explicit AdjacencyGraph(unsigned long int size);
    explicit AdjacencyGraph(const AdjacencyGraph* from);
    explicit AdjacencyGraph(const EdgeGraph<TVertex,TWeight>& from);
    ~AdjacencyGraph() = default;
    AdjacencyGraph(const AdjacencyGraph&) = delete; // according to five-rule
    AdjacencyGraph(AdjacencyGraph&&) = delete;
    AdjacencyGraph& operator=(const AdjacencyGraph&) = delete;
    AdjacencyGraph& operator=(AdjacencyGraph&&) = delete;




    void Add(TVertex from, TVertex to, TWeight weight);
    std::vector<TVertex> dfs(TVertex start_vertex) const;
    unsigned long int size() const;
    std::vector<std::pair<int, double>>::const_iterator adjasentBegin(TVertex vertex) const;
    std::vector<std::pair<int, double>>::const_iterator adjasentEnd(TVertex vertex) const;
private:
    std::vector<std::vector<std::pair<TVertex, TWeight>>> adjacencyList;
};