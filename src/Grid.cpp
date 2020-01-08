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

	m_eStateToApply = ECaseState::Empty;
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

void Grid::OnMouseClicked(int posX, int posY)
{
	int x = posY / CASE_SIZE;
	int y = posX / CASE_SIZE;

	m_eStateToApply = m_aaGrid[x][y].GetState();

	if (ECaseState::Wall == m_eStateToApply)
		m_eStateToApply = ECaseState::Empty;
	else if (ECaseState::Empty == m_eStateToApply)
		m_eStateToApply = ECaseState::Wall;

	m_aaGrid[x][y].SetState(m_eStateToApply);
}

void Grid::OnMouseMoved(int posX, int posY)
{
	if (posX < 0 || posY < 0)
		return;

	int x = posY / CASE_SIZE;
	int y = posX / CASE_SIZE;

	m_aaGrid[x][y].SetState(m_eStateToApply);
}
