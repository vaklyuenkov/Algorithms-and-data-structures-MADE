#pragma once

#include "EdgeGraph.hpp"

class MST {
public:
    explicit MST(EdgeGraph& graph);
    ~MST() = default;
    MST(const MST&) = delete; // according to five-rule
    MST(MST&&) = delete;
    MST& operator=(const MST&) = delete;
    MST& operator=(MST&&) = delete;

    EdgeGraph getTree() const;

private:
    EdgeGraph tree;
};