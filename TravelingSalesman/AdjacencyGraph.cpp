#include <stack>
#include "AdjacencyGraph.hpp"

template <class TVertex, class TWeight>
AdjacencyGraph< TVertex, TWeight>::AdjacencyGraph() = default;

template <class TVertex, class TWeight>
AdjacencyGraph< TVertex, TWeight>::AdjacencyGraph(unsigned long int size)
{
    adjacencyList.resize(size);
}

template <class TVertex, class TWeight>
AdjacencyGraph< TVertex, TWeight>::AdjacencyGraph(const AdjacencyGraph* from): AdjacencyGraph(from->size())
{
    this->adjacencyList = from->adjacencyList;
}

template <class TVertex, class TWeight>
AdjacencyGraph< TVertex, TWeight>::AdjacencyGraph(const EdgeGraph<TVertex, TWeight>& from) : AdjacencyGraph(from.size())
{
    for(auto edge: from)
    {
        Add(edge.from, edge.to, edge.weight);
    }
}

template <class TVertex, class TWeight>
void AdjacencyGraph< TVertex, TWeight>::Add(TVertex from, TVertex to, TWeight weight)
{
    adjacencyList[from].emplace_back(std::make_pair(to, weight));
}

template <class TVertex, class TWeight>
std::vector<TVertex> AdjacencyGraph< TVertex, TWeight>::dfs(TVertex start_vertex) const
{
    std::vector<TVertex> path;
    std::vector<bool> visited(size(), false);
    std::stack<TVertex> dfsStack;
    dfsStack.push(start_vertex);
    visited[start_vertex] = true;
    while(!dfsStack.empty())
    {
        TVertex current_vertex = dfsStack.top();
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

template <class TVertex, class TWeight>
unsigned long int AdjacencyGraph< TVertex, TWeight>::size() const
{
    return adjacencyList.size();
}

template <class TVertex, class TWeight>
std::vector<std::pair<int, double>>::const_iterator AdjacencyGraph< TVertex, TWeight>::adjasentBegin(TVertex vertex) const {
    return adjacencyList[vertex].cbegin();
}

template <class TVertex, class TWeight>
std::vector<std::pair<int, double>>::const_iterator AdjacencyGraph< TVertex, TWeight>::adjasentEnd(TVertex vertex) const
{
    return adjacencyList[vertex].cend();
}

template class AdjacencyGraph<int, double>;