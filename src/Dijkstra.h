#pragma once

#include "Pathfinding.h"

class Dijkstra : public Pathfinding
{
public:
	virtual void Initialize(Grid& grid) override;

	virtual bool Execute(void) override;

private:
	void ComputeMinDistNodeInQueue(void);
	void ComputeNeighboursOfCurrent(std::vector<std::pair<int, int>>& aNeighbours);

private:
	struct SDatas
	{
		bool bVisited; // TODO move this in base grid ?
		int distance;
		std::pair<int, int> previous;
	};

	SDatas m_aaWorker[GRID_SIZE][GRID_SIZE];

	std::vector<std::pair<int, int>> m_aNodeQueue;

	std::pair<int, int> m_vCurrentNode;
};
