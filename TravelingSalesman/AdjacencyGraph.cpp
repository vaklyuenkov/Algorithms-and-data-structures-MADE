#include <stack>
#include "AdjacencyGraph.hpp"

AdjacencyGraph::AdjacencyGraph() = default;
AdjacencyGraph::AdjacencyGraph(unsigned long int size)
{
    adjacencyList.resize(size);
}

AdjacencyGraph::AdjacencyGraph(const AdjacencyGraph* from): AdjacencyGraph(from->size())
{
    this->adjacencyList = from->adjacencyList;
}

AdjacencyGraph::AdjacencyGraph(const EdgeGraph& from) : AdjacencyGraph(from.size())
{
    for(auto edge: from)
    {
        Add(edge.from, edge.to, edge.weight);
    }
}

void AdjacencyGraph::Add(int from, int to, double weight)
{
    adjacencyList[from].emplace_back(std::make_pair(to, weight));
}

std::vector<int> AdjacencyGraph::dfs(int start_vertex) const
{
    std::vector<int> path;
    std::vector<bool> visited(size(), false);
    std::stack<int> dfsStack;
    dfsStack.push(start_vertex);
    visited[start_vertex] = true;
    while(!dfsStack.empty())
    {
        int current_vertex = dfsStack.top();
        dfsStack.pop();
        path.push_back(current_vertex);
        for(int i = 0; i < adjacencyList[current_vertex].size(); ++i)
        {
            if(!visited[adjacencyList[current_vertex][i].first])
            {
                dfsStack.push(adjacencyList[current_vertex][i].first);
                visited[adjacencyList[current_vertex][i].first] = true;
            }
        }
    }
    return path;
}

unsigned long int AdjacencyGraph::size() const
{
    return adjacencyList.size();
}

std::vector<std::pair<int, double>>::const_iterator AdjacencyGraph::adjasentBegin(int vertex) const {
    return adjacencyList[vertex].cbegin();
}

std::vector<std::pair<int, double>>::const_iterator AdjacencyGraph::adjasentEnd(int vertex) const
{
    return adjacencyList[vertex].cend();
}