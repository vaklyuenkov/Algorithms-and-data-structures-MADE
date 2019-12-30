#pragma once

#include <vector>

class NotOverlappingSets
{
public:
    explicit NotOverlappingSets(int size);
    ~NotOverlappingSets() = default;
    NotOverlappingSets(const NotOverlappingSets&) = delete; // according to five-rule
    NotOverlappingSets(NotOverlappingSets&&) = delete;
    NotOverlappingSets& operator=(const NotOverlappingSets&) = delete;
    NotOverlappingSets& operator=(NotOverlappingSets&&) = delete;

    void unionSets(int firstVertex, int secondVertex);
    int find(int vertex);

private:

    std::vector<int> parents;
    std::vector<int> rank;
};