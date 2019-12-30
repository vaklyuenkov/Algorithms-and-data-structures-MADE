#pragma once

#include <vector>

class Tests {
public:
    Tests(int from, int to, int num_of_repetitions);
    ~Tests() = default;
    Tests(const Tests&) = delete; // according to five-rule
    Tests(Tests&&) = delete;
    Tests& operator=(const Tests&) = delete;
    Tests& operator=(Tests&&) = delete;

    void printComparison() const;
private:
    void testPoints(int numOfPoints, int numRepetitions);
    int from;
    int to;
    std::vector<double> meanRatio;
    std::vector<double> standartDeviationOfRatio;
};