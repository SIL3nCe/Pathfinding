#pragma once

#include "../GridWorker.h"
#include "../Utility.h"
#include <queue>

class BreadthFirst
{
public:
	void Execute(const GridWorker& Grid, bool bUseDiagonal, std::vector<std::pair<int, int>>& aFinalPath, void(*OnDoingOperation)(EOperations, const std::pair<int, int>&) = DefaultOnDoingOperation);

private:
	struct SDatas
	{
		bool bDiscovered;
		std::pair<int, int> vParent;
	};

	std::vector<std::pair<int, int>> m_aNeighbours;
};
