#include "Utility.h"

#include <algorithm>
#include <cmath>
using namespace std;

// fct(x,y) : |x1 - x2| + |y1 - y2|
int GetManhattanDistance(const pair<int, int>& start, const pair<int, int>& end)
{
	return abs(start.first - end.first) + abs(start.second - end.second);
}

// fct(x,y) : sqrt((y1 - x1)^2 + (y2 - x2)^2)
float GetEuclideanDistance(const pair<int, int>& start, const pair<int, int>& end)
{
	return sqrt(pow(end.first - start.first, 2) + pow(end.second - start.second, 2));
}

// fct(x,y) : Max(|x1 - x2|, |y1 - y2|)
int GetChebyshevDistance(const pair<int, int>& start, const pair<int, int>& end)
{
	return max(abs(start.first - start.second), abs(end.first - end.second));
}
