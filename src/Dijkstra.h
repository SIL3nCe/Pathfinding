#pragma once

#include "Pathfinding.h"

class Dijkstra : public Pathfinding
{
public:
	virtual void Initialize(Grid& grid) override;

	virtual void Execute(void) override;

private:
	struct SDatas 
	{
		bool bVisited;
		float fDistance;
		std::pair<int, int> previous;
	};

	SDatas m_aaWorker[GRID_SIZE][GRID_SIZE];

	std::vector<std::pair<int, int>> aNodeQueue;
};
