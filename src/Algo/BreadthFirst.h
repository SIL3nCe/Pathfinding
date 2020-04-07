#pragma once

#include "../GridWorker.h"
#include <queue>

class BreadthFirst
{
public:
	std::vector<std::pair<int, int>>& Execute(const GridWorker& Grid, bool bUseDiagonal);

private:
	struct SDatas
	{
		bool bDiscovered;
		std::pair<int, int> vParent;
	};

	std::vector<std::vector<SDatas>> m_aaWorker;

	std::vector<std::pair<int, int>> m_aNeighbours;

	std::vector<std::pair<int, int>> m_aFinalPath;

	std::pair<int, int> m_vCurrentNode;
};
