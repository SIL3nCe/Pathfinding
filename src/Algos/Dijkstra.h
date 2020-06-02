#pragma once

#include "GridWorker.h"
#include "Utility.h"

class Dijkstra
{
public:
	static bool Execute(const GridWorker& Grid, bool bUseDiagonal, std::vector<std::pair<int, int>>& aFinalPath, OnDoingOperationFctPtr OnDoingOperation = DefaultOnDoingOperation);

private:
	struct SDatas
	{
		bool bQueued = false;
		float fDistance = static_cast<float>(UINT_MAX - 1);
		std::pair<int, int> vPrevious = { -1, -1 };
	};
};
