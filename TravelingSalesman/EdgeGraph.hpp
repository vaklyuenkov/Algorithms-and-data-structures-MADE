#pragma once

#include <vector>

template <class TVertex, class TWeight>
struct Edge {
    Edge();
    Edge(TVertex from, TVertex to, TWeight weight);

    TVertex from;
    TVertex to;
    TWeight weight;
};

template <class TVertex, class TWeight>
class EdgeGraph {
public:
    EdgeGraph();
    explicit EdgeGraph(int size);
    explicit EdgeGraph(const EdgeGraph* from);
    ~EdgeGraph() = default;

    void add(TVertex from, TVertex to, TWeight weight);
    int edgesNum() const;
    int size() const;
    typename std::vector<Edge<TVertex,TWeight>>::const_iterator begin() const;
    typename std::vector<Edge<TVertex,TWeight>>::const_iterator end() const;
private:
    std::vector<Edge<TVertex,TWeight>> edges;
    int graph_size;
};