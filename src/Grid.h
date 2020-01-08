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
	
	void Onclicked(int posX, int posY);

private:
	Case m_aaGrid[GRID_SIZE][GRID_SIZE];
};

