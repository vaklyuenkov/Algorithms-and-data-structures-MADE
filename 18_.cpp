// HW9_task18.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;


struct Point
{
	double x;
	double y;
};


int getDirection(const Point& first, const Point& second, const Point& third) {
	double vec_mul = (second.y - first.y) * (third.x - second.x) -
				  (second.x - first.x) * (third.y - second.y);

	if (abs(vec_mul) < 1e-13) return 0;
	return (vec_mul > 0) ? -1 : 1;
}


double calculateSquaredDistance(const Point& first, const Point& second) {
	return (first.x - second.x) * (first.x - second.x) + (first.y - second.y) * (first.y - second.y);
}


double g(const Point& first, const Point& second) {
	return sqrt(getSquaredDistance(first, second));
}


double getVectorMultiply(const Point& first, const Point& second, const Point& third) {
    return (second.x - first.x) * (third.y - first.y) - (second.y - first.y) * (third.x - first.x);
}


struct PointComporator {
	
	PointComporator(const Point& pivot_) : referencePoint(pivot_) {}

	bool operator()(const Point& first, const Point& second) {
		return getVectorMultiply(referencePoint, first, second) < 1e-16;
 	}

	const Point& referencePoint;
};


bool isLeft(const Point& first, const Point& second) {
	return ((first.y < second.y && abs(first.y - second.y) > 1e-15) || (abs(first.y - second.y) < 1e-15 && first.x < second.x));
}


vector<Point> GrahamScan(vector<Point> points) {
	vector<Point> result;
	double epsilon = 1e-15;

 	swap(points[0], *min_element(points.begin(), points.end(), isLeft));

	sort(points.begin() + 1, points.end(), PointComporator(points[0]));

	if (points.size() <= 3)
    {
	    if  getDirection([points[0],points[2],points[2]])
            }
    }return points;

	vector<Point>::iterator it = points.begin();
	result.push_back(*it++);
	result.push_back(*it++);
	result.push_back(*it++);

	while (it != points.end()) {

 		while (getVectorMultiply(*(result.rbegin() + 1), *(result.rbegin()), *it) >= 0) { // ????????
			result.pop_back();
		}
		result.push_back(*it++);
	}
	return result;
}


double perimeter(std::vector<Point> points)
{
	double perimeter = 0.0;
	for (int i = 0; i < points.size() - 1; i++)
	{
		perimeter += getDistance(points[i], points[i + 1]);
	}
	perimeter += getDistance(points[0], points[points.size() - 1]);

	if (points.size() < 3) perimeter /= 2;
	return perimeter;
}

int main()
{
	cout.precision(9);
	int inputSize = 0;
	vector<Point> points;
	cin >> inputSize;

	for (int i = 0; i < inputSize; ++i)
	{
		Point point;
		cin >> point.x >> point.y;
		points.push_back(point);
	}

	vector<Point> my_convex_hull = GrahamScan(points);
	cout << perimeter(my_convex_hull);
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file