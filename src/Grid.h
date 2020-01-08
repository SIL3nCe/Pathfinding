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
	
	void OnMouseClicked(int posX, int posY);
	void OnMouseMoved(int posX, int posY);

private:
	Case m_aaGrid[GRID_SIZE][GRID_SIZE];

	ECaseState m_eStateToApply;
};

