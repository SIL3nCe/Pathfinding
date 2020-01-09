#pragma once

#include "Case.h"

#define GRID_SIZE 50
#define CASE_SIZE 20.0f
#define CASE_OUTLINE_SIZE 2

class Grid
{
public:
	void Initialize(void);

	void Draw(sf::RenderWindow & window);
	
	void Reset(void);

	void OnMouseClicked(int posX, int posY);
	void OnMouseMoved(int posX, int posY);
	void OnMouseReleased(void);

private:
	Case m_aaGrid[GRID_SIZE][GRID_SIZE];
	std::pair<int, int> m_vStart;
	std::pair<int, int> m_vEnd;

	ECaseState m_eStateToApply;
};

