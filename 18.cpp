/*
Автор: Клюенков Владимир vaklyuenkov@gmail.com
Дата: 30.12.19

Задача 18. Построение выпуклой оболочки.

Дано множество точек на плоскости (x, y).
Постройте выпуклую оболочку этого множества и вычислите ее периметр.
Вариант 1. С помощью алгоритма Грэхема.
Обратите внимание: три и более точки из множества могут лежать на одной прямой.

Формат входного файла:
    Количество точек, далее на каждой строке координаты точек x, y.
    Общее количество точек не превосходит 100000.
    Координаты точек - числа с плавающей точкой в диапазоне [-1000, 1000].

Формат выходного файла:
    Выведите периметр выпуклой оболочки.
Время: 100мс, память 3Mb.

stdin:
3
1. 1.
2. 1.
0. 0.

stdout:
4.65028154
*/

#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

struct TwoDPoint
{
    double x;
    double y;
};



double calculateSquaredDistance(const TwoDPoint& firstPoint, const TwoDPoint& secondPoint)
{
    return (firstPoint.x - secondPoint.x) * (firstPoint.x - secondPoint.x) + (firstPoint.y - secondPoint.y) * (firstPoint.y - secondPoint.y);
}

double calculateDistance(const TwoDPoint& firstPoint, const TwoDPoint& secondPoint)
{
    return sqrt(calculateSquaredDistance(firstPoint, secondPoint));
}

double CalculateVectorMultiplication(const TwoDPoint& firstPoint, const TwoDPoint& secondPoint, const TwoDPoint& thirdPoint)
{
    double result = (secondPoint.x - firstPoint.x) * (thirdPoint.y - secondPoint.y) - (secondPoint.y - firstPoint.y) * (thirdPoint.x - secondPoint.x);
    return result;
}

struct ComparatorWithReferencePoint
{

    ComparatorWithReferencePoint(const TwoDPoint& referencePoint_) : referencePoint(referencePoint_) {}

    bool operator()(const TwoDPoint& firstPoint, const TwoDPoint& secondPoint)
    {
        double multiplication = CalculateVectorMultiplication(secondPoint, firstPoint, referencePoint);
        if (multiplication == 0)
        {
            return (calculateDistance(secondPoint, referencePoint) < calculateDistance(firstPoint, referencePoint));
        }
        return multiplication < 1e-10; // with accuracy epsilon
    }

    const TwoDPoint& referencePoint;
};


double CalculatePerimeter(std::vector<TwoDPoint> points)
{
    assert(points.size() > 1);
    double perimeter = 0.0;
    for (int i = 0; i < points.size() - 1; ++i)
    {
        perimeter += calculateDistance(points[i], points[i + 1]);
    }
    perimeter += calculateDistance(points[0], points[points.size() - 1]);
    return perimeter;
}


vector<TwoDPoint> BuildConvexHull(vector<TwoDPoint> points) {
    vector<TwoDPoint> convexHull;
    int indexOfReferencePoint = 0;
    for (int i = 0; i < points.size(); ++i) {
        if (points[i].x < points[indexOfReferencePoint].x) indexOfReferencePoint = i;
    }
    swap(points[0], points[indexOfReferencePoint]);

    sort(points.begin() + 1, points.end(), ComparatorWithReferencePoint(points[0]));

    convexHull.push_back(points[0]);
    convexHull.push_back(points[1]);

    for (int i = 2; i < points.size(); i++)
    {
        while (CalculateVectorMultiplication(*(convexHull.rbegin() + 1), *(convexHull.rbegin()), points[i]) < 1e-11 && convexHull.size() > 2)  // with accuracy epsilon
        {
            convexHull.pop_back();
        }
        convexHull.push_back(points[i]);
    }

    return convexHull;
}


int main()
{
    int inputSize = 0;
    std::vector<TwoDPoint> points;
    std::cin >> inputSize;
    assert(inputSize <= 100000);

    for (int i = 0; i<inputSize; i++)
    {
        TwoDPoint point;
        std::cin >> point.x >> point.y;
        points.push_back(point);
    }
    double answer = 0;
    cout.precision(9);
    vector<TwoDPoint> convexHull = BuildConvexHull(points);
    if (convexHull.size() > 2)
    {
        answer = CalculatePerimeter(convexHull);
    }
    cout << answer;
    return 0;
}