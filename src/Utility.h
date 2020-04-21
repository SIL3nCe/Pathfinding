#pragma once

#include <utility>

//TODO debug only
#include <iostream>

constexpr float SquareRootOf2 = 1.41421356237309504880f;

std::pair<int, int> operator+(const std::pair<int, int>& l, const std::pair<int, int>& r);

enum class EOperations : unsigned int
{
	QueuedNode,
	ClosedNode
};

void DefaultOnDoingOperation(EOperations eOperation, const std::pair<int, int>& vCellCoord);

struct SOperation
{
	EOperations eOperation;
	std::pair<int, int> vCellCoord;
};

enum class EHeuristic : unsigned int
{
	Manhattan,
	Euclidean,
	Chebyshev,
	Null
};

class Utility
{
public:
	static int		GetManhattanDistance(const std::pair<int, int>& start, const std::pair<int, int>& end);
	static float	GetEuclideanDistance(const std::pair<int, int>& start, const std::pair<int, int>& end);
	static int		GetChebyshevDistance(const std::pair<int, int>& start, const std::pair<int, int>& end);

public:
	static const std::pair<int, int> CellTop;
	static const std::pair<int, int> CellRight;
	static const std::pair<int, int> CellBottom;
	static const std::pair<int, int> CellLeft;

	static const std::pair<int, int> CellTopLeft;
	static const std::pair<int, int> CellTopRight;
	static const std::pair<int, int> CellBottomLeft;
	static const std::pair<int, int> CellBottomRight;
};
