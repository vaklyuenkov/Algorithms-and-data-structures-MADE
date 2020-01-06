#pragma once

#include <vector>

template <class TVertex>
class NotOverlappingSets
{
public:
    explicit NotOverlappingSets(int size);
    ~NotOverlappingSets() = default;
    NotOverlappingSets(const NotOverlappingSets&) = delete; // according to five-rule
    NotOverlappingSets(NotOverlappingSets&&) = delete;
    NotOverlappingSets& operator=(const NotOverlappingSets&) = delete;
    NotOverlappingSets& operator=(NotOverlappingSets&&) = delete;

    void unionSets(TVertex firstVertex, TVertex secondVertex);
    int find(TVertex vertex);

private:

    std::vector<TVertex> parents;
    std::vector<TVertex> rank;
};