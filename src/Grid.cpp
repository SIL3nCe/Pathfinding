#include "Grid.h"

void Grid::Initialize(void)
{
	int posX = 0, posY = 0;
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			m_aaGrid[i][j].setSize(sf::Vector2f(CASE_SIZE, CASE_SIZE));
			m_aaGrid[i][j].setPosition(sf::Vector2f(posX, posY));
			posX += CASE_SIZE + CASE_SPACE;
		}

		posX = 0.0f;
		posY += CASE_SIZE + CASE_SPACE;
	}
}

void Grid::Draw(sf::RenderWindow & window)
{
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			window.draw(m_aaGrid[i][j]);
		}
	}
}

void Grid::Onclicked(int x, int y)
{
	printf("%i, %i\n", x, y);
}
