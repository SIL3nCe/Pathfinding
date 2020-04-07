#pragma once

#include "../GridWorker.h"

class Dijkstra
{
public:
	std::vector<std::pair<int, int>>& Execute(const GridWorker& Grid, bool bUseDiagonal);

private:
	void ComputeMinDistNodeInQueue(std::vector<std::pair<int, int>>& aQueue);

private:
	struct SDatas
	{
		float fDistance;
		std::pair<int, int> vPrevious;
	};

	std::vector<std::vector<SDatas>> m_aaWorker;

	std::vector<std::pair<int, int>> m_aNeighbours;

	std::vector<std::pair<int, int>> m_aFinalPath;

	std::pair<int, int> m_vCurrentNode;
};
