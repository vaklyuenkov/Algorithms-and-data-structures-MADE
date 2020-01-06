#include "NotOverlappingSets.hpp"

template <class TVertex>
NotOverlappingSets<TVertex>::NotOverlappingSets(int size
) {
    parents.resize(size);
    rank.resize(size, 0);
    for(int i = 0; i < parents.size(); ++i) {
        parents[i] = i;
    }
}

template <class TVertex>
void NotOverlappingSets<TVertex>::unionSets(TVertex firstVertex, TVertex secondVertex)
{
    if((firstVertex = find(firstVertex)) == (secondVertex = find(secondVertex)))
    {
        return;
    }
    if(rank[firstVertex] < rank[secondVertex])
    {
        parents[firstVertex] = secondVertex;
    }
    else
    {
        parents[secondVertex] = firstVertex;

        if(rank[firstVertex] == rank[secondVertex])
        {
            ++rank[firstVertex];
        }
    }
}

template <class TVertex>
int NotOverlappingSets<TVertex>::find(TVertex vertex)
{
    if(vertex == parents[vertex])
    {
        return vertex;
    }
    else
    {
        int value = find(parents[vertex]);
        parents[vertex] = value;
        return value;
    }
}

template class NotOverlappingSets<int>;