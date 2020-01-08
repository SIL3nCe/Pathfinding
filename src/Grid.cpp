#include "Grid.h"

void Grid::Initialize(void)
{
	int posX = 0, posY = 0;
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			m_aaGrid[i][j].Initialize(CASE_SIZE, CASE_OUTLINE_SIZE, sf::Vector2f(posX, posY));
			posX += CASE_SIZE;
		}

		posX = 0.0f;
		posY += CASE_SIZE;
	}
}

void Grid::Draw(sf::RenderWindow & window)
{
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			m_aaGrid[i][j].Draw(window);
		}
	}
}

void Grid::Onclicked(int posX, int posY)
{
	int x = posY / CASE_SIZE;
	int y = posX / CASE_SIZE;
	m_aaGrid[x][y].SetState(ECaseState::Wall); // TODO Handle state to set in main (keyboard key to switch between empty/wall ? + drag&drop by default when no key pressed even for walls
}
