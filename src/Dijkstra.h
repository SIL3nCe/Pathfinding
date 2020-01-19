#pragma once

#include "Pathfinding.h"

class Dijkstra : public Pathfinding
{
public:
	virtual void Start(void) override;
	virtual bool Execute(void) override;
	virtual void Stop(void) override;

private:
	void ComputeMinDistNodeInQueue(void);
	void ComputeNeighboursOfCurrent(void);

private:
	struct SDatas
	{
		int distance;
		std::pair<int, int> vPrevious;
	};

	SDatas m_aaWorker[GRID_SIZE][GRID_SIZE];

	std::vector<std::pair<int, int>> m_aNodeQueue;
	std::vector<std::pair<int, int>> m_aNeighbours;

	std::pair<int, int> m_vCurrentNode;
};
