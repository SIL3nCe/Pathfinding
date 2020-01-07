#pragma once

#include <SFML/Graphics.hpp>

#define GRID_SIZE 50
#define CASE_SIZE 20.0f
#define CASE_SPACE 2

class Grid
{
public:
	void Initialize(void);

	void Draw(sf::RenderWindow & window);
	
	void Onclicked(int x, int y);

private:
	sf::RectangleShape m_aaGrid[GRID_SIZE][GRID_SIZE];
};

