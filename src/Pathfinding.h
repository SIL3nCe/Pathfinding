#pragma once

#include "Grid.h"
#include "Utility.h"

// Base class to inherit in algorithm classes
class Pathfinding
{
public:
	virtual void Initialize(Grid& grid);

	virtual bool Execute(void) = 0;

protected:
	Grid * m_pGrid;
};
