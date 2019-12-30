#include "NotOverlappingSets.hpp"

NotOverlappingSets::NotOverlappingSets(int size
) {
    parents.resize(size);
    rank.resize(size, 0);
    for(int i = 0; i < parents.size(); ++i) {
        parents[i] = i;
    }
}
void NotOverlappingSets::unionSets(int firstVertex, int secondVertex)
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
int NotOverlappingSets::find(int vertex)
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