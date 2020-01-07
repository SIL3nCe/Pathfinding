#pragma once

#include <SFML/Graphics.hpp>

#define GRID_SIZE 50
#define CASE_SIZE 5.0f

class Grid
{
public:
	void Initialize(void);

	void Draw(sf::RenderWindow & window);

private:
	sf::RectangleShape m_aaGrid[GRID_SIZE][GRID_SIZE];
};

