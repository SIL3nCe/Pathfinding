#pragma once

#include "GridWorker.h"
#include "Utility.h"
#include <queue>

class BreadthFirst
{
public:
	bool Execute(const GridWorker& Grid, bool bUseDiagonal, std::vector<std::pair<int, int>>& aFinalPath, OnDoingOperationFctPtr OnDoingOperation = DefaultOnDoingOperation);

private:
	struct SDatas
	{
		bool bDiscovered;
		std::pair<int, int> vParent;
	};

	std::vector<std::pair<int, int>> m_aNeighbours;
};
