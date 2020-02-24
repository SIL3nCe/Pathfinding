#include "Utility.h"

#include <algorithm>
#include <cmath>
using namespace std;

const pair<int, int> Utility::CellTop(-1, 0);
const pair<int, int> Utility::CellRight(0, 1);
const pair<int, int> Utility::CellBottom(1, 0);
const pair<int, int> Utility::CellLeft(0, -1);

const pair<int, int> Utility::CellTopLeft(-1, -1);
const pair<int, int> Utility::CellTopRight(-1, 1);
const pair<int, int> Utility::CellBottomLeft(1, -1);
const pair<int, int> Utility::CellBottomRight(1, 1);

std::pair<int, int> operator+(const std::pair<int, int>& l, const std::pair<int, int>& r)
{
	return std::make_pair(l.first + r.first, l.second + r.second);
}

// fct(x,y) : |x1 - x2| + |y1 - y2|
/*static*/ int Utility::GetManhattanDistance(const pair<int, int>& start, const pair<int, int>& end)
{
	return abs(start.first - end.first) + abs(start.second - end.second);
}

// fct(x,y) : sqrt((y1 - x1)^2 + (y2 - x2)^2)
/*static*/ float Utility::GetEuclideanDistance(const pair<int, int>& start, const pair<int, int>& end)
{
	return sqrt(pow(end.first - start.first, 2) + pow(end.second - start.second, 2));
}

// fct(x,y) : Max(|x1 - x2|, |y1 - y2|)
/*static*/ int Utility::GetChebyshevDistance(const pair<int, int>& start, const pair<int, int>& end)
{
	return max(abs(start.first - start.second), abs(end.first - end.second));
}
