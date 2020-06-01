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

pair<int, int> operator+(const pair<int, int>& l, const pair<int, int>& r)
{
	return make_pair(l.first + r.first, l.second + r.second);
}

void DefaultOnDoingOperation(EOperations eOperation, const std::pair<int, int>& vCellCoord)
{
}

// fct(a,b) : |bx - ax| + |by - ay|
/*static*/ int Utility::GetManhattanDistance(const pair<int, int>& start, const pair<int, int>& end)
{
	return abs(end.first - start.first) + abs(end.second - start.second);
}

// fct(a,b) : sqrt((bx - ax)^2 + (by - ay)^2)
/*static*/ float Utility::GetEuclideanDistance(const pair<int, int>& start, const pair<int, int>& end)
{
	return sqrt(pow(end.first - start.first, 2) + pow(end.second - start.second, 2));
}

// fct(a,b) : Max(|bx - ax|, |by - ay|)
/*static*/ int Utility::GetChebyshevDistance(const pair<int, int>& start, const pair<int, int>& end)
{
	return max(abs(end.first - start.first), abs(end.second - start.second));
}
