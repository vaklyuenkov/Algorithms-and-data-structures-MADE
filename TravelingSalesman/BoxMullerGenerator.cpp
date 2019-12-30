#include <cmath>
#include <random>
#include "BoxMullerGenerator.hpp"

BoxMullerGenerator::BoxMullerGenerator(int n)
{
    generate_points(n);
}

void BoxMullerGenerator::generate_points(int n)
{
    points = {};
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    for(int i = 0; i < n; ++i) {
        double radius = dis(gen);
        double phi = dis(gen);
        double twoPiM = std::cos(2 * M_PI * phi);
        double sqrtLogRad = sqrt(-2 * std::log(radius));
        double x = twoPiM * sqrtLogRad;
        double y = sqrt(1 - twoPiM * twoPiM) * sqrtLogRad;
        points.emplace_back(std::make_pair(x, y));
    }
}

std::vector<std::pair<double, double>> BoxMullerGenerator::getPoints() const
{
    return points;
}