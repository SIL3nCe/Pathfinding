#pragma once

#include "../Grid.h"
#include "../Utility.h"
#include "imgui.h"

// Base class to inherit in algorithm classes
class Pathfinding
{
public:
	virtual void Initialize(Grid& grid, sf::Font& font);

	// Begin, init datas
	virtual void Start(void);

	// Async exec of algo
	virtual bool Execute(void) = 0;

	// End, compute path
	virtual void Stop(void);

	// Draw GUI
	virtual void DrawGui(void) = 0;

	// Draw additional debug info from algo
	virtual void Draw(sf::RenderWindow& window) = 0;
	// Clear debug infos
	virtual void Clear(void) = 0;

	virtual void DrawGuiStatistics(void);

public:
	bool m_bGuiOpen; // Flag to know if algo Gui is open or not

protected:
	Grid * m_pGrid;

	sf::Font * m_pFont;

	// Stats
	float m_fLength;

	sf::Clock m_clock;
	float m_fTime;

	sf::Clock m_asynClock;
	float m_fAsyncTime;

	int m_steps;
};
