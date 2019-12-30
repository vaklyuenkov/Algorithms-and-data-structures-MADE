#pragma once

#include <vector>

struct Edge {
    Edge();
    Edge(int from, int to, double weight);

    int from;
    int to;
    double weight;
};

class EdgeGraph {
public:
    EdgeGraph();
    explicit EdgeGraph(int size);
    explicit EdgeGraph(const EdgeGraph* from);
    ~EdgeGraph() = default;

    void add(int from, int to, double weight);
    int edgesNum() const;
    int size() const;
    std::vector<Edge>::const_iterator begin() const;
    std::vector<Edge>::const_iterator end() const;
private:
    std::vector<Edge> edges;
    int graph_size;
};