#pragma once

#include "EdgeGraph.hpp"

template <class TVertex, class TWeight>
class MST {
public:
    explicit MST(EdgeGraph<TVertex, TWeight>& graph);
    ~MST() = default;
    MST(const MST&) = delete; // according to five-rule
    MST(MST&&) = delete;
    MST& operator=(const MST&) = delete;
    MST& operator=(MST&&) = delete;

    EdgeGraph<TVertex, TWeight> getTree() const;

private:
    EdgeGraph<TVertex, TWeight> tree;
};