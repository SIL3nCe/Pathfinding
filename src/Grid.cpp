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

		posX = 0;
		posY += CASE_SIZE;
	}

	// Setup Start&End
	m_vStart.first = GRID_SIZE / 2;
	m_vStart.second = std::max(GRID_SIZE / 2 - 5, 0);
	m_aaGrid[m_vStart.first][m_vStart.second].SetState(ECellState::Start);

	m_vEnd.first = GRID_SIZE / 2;
	m_vEnd.second= std::min(GRID_SIZE / 2 + 5, GRID_SIZE - 1);
	m_aaGrid[m_vEnd.first][m_vEnd.second].SetState(ECellState::End);

	m_eStateToApply = ECellState::Empty;
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

void Grid::Clear(void)
{
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			if (ECellState::Empty == m_aaGrid[i][j].GetState())
			{
				m_aaGrid[i][j].SetColor(sf::Color::White);
			}
		}
	}
}

void Grid::Reset(void)
{
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			m_aaGrid[i][j].SetState(ECellState::Empty, true);
		}
	}

	// Setup Start&End
	m_vStart.first = GRID_SIZE / 2;
	m_vStart.second = std::max(GRID_SIZE / 2 - 5, 0);
	m_aaGrid[m_vStart.first][m_vStart.second].SetState(ECellState::Start);

	m_vEnd.first = GRID_SIZE / 2;
	m_vEnd.second = std::min(GRID_SIZE / 2 + 5, GRID_SIZE - 1);
	m_aaGrid[m_vEnd.first][m_vEnd.second].SetState(ECellState::End);
}

// Used to mark treated cases during alogirthms execution
void Grid::SetCaseColor(const std::pair<int, int>& vCase, const sf::Color& color)
{
	if (vCase == m_vStart || vCase == m_vEnd)
		return;

	m_aaGrid[vCase.first][vCase.second].SetColor(color);
}

void Grid::OnMouseClicked(int posX, int posY)
{
	int x = posY / CASE_SIZE;
	int y = posX / CASE_SIZE;

	if (!IsValidID(x, y))
		return;

	m_eStateToApply = m_aaGrid[x][y].GetState();

	if (ECellState::Wall == m_eStateToApply)
		m_eStateToApply = ECellState::Empty;
	else if (ECellState::Empty == m_eStateToApply)
		m_eStateToApply = ECellState::Wall;

	m_aaGrid[x][y].SetState(m_eStateToApply);
}

void Grid::OnMouseMoved(int posX, int posY)
{
	int x = posY / CASE_SIZE;
	int y = posX / CASE_SIZE;

	if (!IsValidID(x, y))
		return;

	if (ECellState::Start == m_eStateToApply)
	{
		if (ECellState::End == m_aaGrid[x][y].GetState())
			return;

		m_aaGrid[m_vStart.first][m_vStart.second].SetState(ECellState::Empty, true);
		m_vStart.first = x;
		m_vStart.second = y;
	}
		
	if (ECellState::End == m_eStateToApply)
	{
		if (ECellState::Start == m_aaGrid[x][y].GetState())
			return;

		m_aaGrid[m_vEnd.first][m_vEnd.second].SetState(ECellState::Empty, true);
		m_vEnd.first = x;
		m_vEnd.second = y;
	}

	m_aaGrid[x][y].SetState(m_eStateToApply);
}

void Grid::OnMouseReleased(void)
{
	m_eStateToApply = ECellState::Empty;
}

bool Grid::IsValidID(const std::pair<int, int>& vNode) const
{
	return IsValidID(vNode.first, vNode.second);
}

inline bool Grid::IsValidID(int x, int y) const
{
	return (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE);
}

bool Grid::IsWalkable(const std::pair<int, int>& vNode) const
{
	return IsWalkable(vNode.first, vNode.second);
}

inline bool Grid::IsWalkable(int x, int y) const
{
	return IsValidID(x, y) && m_aaGrid[x][y].GetState() != ECellState::Wall;
}
