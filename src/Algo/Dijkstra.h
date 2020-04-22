#pragma once

#include "../GridWorker.h"
#include "../Utility.h"

class Dijkstra
{
public:
	bool Execute(const GridWorker& Grid, bool bUseDiagonal, std::vector<std::pair<int, int>>& aFinalPath, void(*OnDoingOperation)(EOperations, const std::pair<int, int>&) = DefaultOnDoingOperation);

private:
	struct SDatas
	{
		bool bQueued;
		float fDistance;
		std::pair<int, int> vPrevious;
	};

	std::vector<std::pair<int, int>> m_aNeighbours;
};
