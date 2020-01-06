#pragma once

#include <vector>
#include <utility>

template <class TCoordinate>
class BoxMullerGenerator {
public:
    explicit BoxMullerGenerator(int n);
    ~BoxMullerGenerator() = default;
    BoxMullerGenerator(const BoxMullerGenerator&) = delete; // according to five-rule
    BoxMullerGenerator(BoxMullerGenerator&&) = delete;
    BoxMullerGenerator& operator=(const BoxMullerGenerator&) = delete;
    BoxMullerGenerator& operator=(BoxMullerGenerator&&) = delete;

    void generate_points(int n);
    std::vector<std::pair<TCoordinate, TCoordinate>> getPoints() const;

private:
    std::vector<std::pair<TCoordinate, TCoordinate>> points;
};