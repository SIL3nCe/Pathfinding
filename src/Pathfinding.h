#pragma once

#include "Grid.h"

// Base class to inherit in algorithm classes
class Pathfinding
{
public:
	virtual void Initialize(Grid& grid);

	virtual void Execute(void) = 0;

protected:
	Grid * m_pGrid;
};
