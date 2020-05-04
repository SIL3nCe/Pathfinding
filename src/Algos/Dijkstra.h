#pragma once

#include "GridWorker.h"
#include "Utility.h"

class Dijkstra
{
public:
	bool Execute(const GridWorker& Grid, bool bUseDiagonal, std::vector<std::pair<int, int>>& aFinalPath, OnDoingOperationFctPtr OnDoingOperation = DefaultOnDoingOperation);

private:
	struct SDatas
	{
		bool bQueued;
		float fDistance;
		std::pair<int, int> vPrevious;
	};

	std::vector<std::pair<int, int>> m_aNeighbours;
};
