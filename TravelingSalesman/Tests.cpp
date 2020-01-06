#include <iostream>
#include <cmath>
#include "BoxMullerGenerator.hpp"
#include "MSTSolver.hpp"
#include "BruteForceSolver.hpp"
#include "Tests.hpp"

Tests::Tests(int from, int to, int num_of_repetitions)
{
    this->from = from;
    this->to = to;
    for(int i = from; i <= to; ++i) {
        testPoints(i, num_of_repetitions);
    }
}

void Tests::printComparison() const
{
    for(int i = from; i <= to; ++i) {
        std::cout.fixed;
        std::cout.precision(4);
        std::cout << "N: " << i << ": " << "average ratio aproximate/accurate decisions: " << meanRatio[i - from] << " Standart deviation:" << standartDeviationOfRatio[i - from] << std::endl;
    }
}

void Tests::testPoints(int numOfPoints, int numRepetitions)
{
    BoxMullerGenerator<double> pointGenerator(numOfPoints);
    std::vector<double> factors(numRepetitions);
    double sumFactors = 0;
    for(int i = 0; i < numRepetitions; ++i) {
        auto points = pointGenerator.getPoints();
        pointGenerator.generate_points(numOfPoints);
        MSTSolver<int, double ,double> MST_solution(points);
        BruteForceSolver<int, double ,double> brute_solution(points);
        factors[i] = MST_solution.getDistance() / brute_solution.getDistance();
        sumFactors += factors[i];
    }
    meanRatio.push_back(sumFactors / numRepetitions);
    double average_difference = sumFactors / numRepetitions;
    double standart_deviation = 0;
    for(auto value: factors) {
        standart_deviation += pow(value - average_difference, 2);
    }
    standart_deviation = sqrt(standart_deviation / numRepetitions);
    standartDeviationOfRatio.push_back(standart_deviation);
}