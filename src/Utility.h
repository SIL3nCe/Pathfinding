#pragma once

#include <utility>

static int		GetManhattanDistance(const std::pair<int, int>& start, const std::pair<int, int>& end);
static float	GetEuclideanDistance(const std::pair<int, int>& start, const std::pair<int, int>& end);
static int		GetChebyshevDistance(const std::pair<int, int>& start, const std::pair<int, int>& end);
