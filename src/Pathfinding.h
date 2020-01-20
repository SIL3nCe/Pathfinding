#pragma once

#include "Grid.h"
#include "Utility.h"

// Base class to inherit in algorithm classes
class Pathfinding
{
public:
	void Initialize(Grid& grid);

	// Begin, init datas
	virtual void Start(void) = 0;

	// Async exec of algo
	virtual bool Execute(void) = 0;

	// End, compute path
	virtual void Stop(void) = 0;

	// Draw additional debug info from algo
	virtual void Draw(sf::RenderWindow& window) = 0;
	// Clear debug infos
	virtual void Clear(void) = 0;

protected:
	Grid * m_pGrid;
};
