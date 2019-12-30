#pragma once

#include <vector>
#include <utility>
#include "EdgeGraph.hpp"

class AdjacencyGraph {
public:
    AdjacencyGraph();
    explicit AdjacencyGraph(unsigned long int size);
    explicit AdjacencyGraph(const AdjacencyGraph* from);
    explicit AdjacencyGraph(const EdgeGraph& from);
    ~AdjacencyGraph() = default;
    AdjacencyGraph(const AdjacencyGraph&) = delete; // according to five-rule
    AdjacencyGraph(AdjacencyGraph&&) = delete;
    AdjacencyGraph& operator=(const AdjacencyGraph&) = delete;
    AdjacencyGraph& operator=(AdjacencyGraph&&) = delete;




    void Add(int from, int to, double weight);
    std::vector<int> dfs(int start_vertex) const;
    unsigned long int size() const;
    std::vector<std::pair<int, double>>::const_iterator adjasentBegin(int vertex) const;
    std::vector<std::pair<int, double>>::const_iterator adjasentEnd(int vertex) const;
private:
    std::vector<std::vector<std::pair<int, double>>> adjacencyList;
};