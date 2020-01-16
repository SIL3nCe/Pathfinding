#include "Grid.h"

void Grid::Initialize(void)
{
	int posX = 5, posY = 5;
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			m_aaGrid[i][j].Initialize(CASE_SIZE, CASE_OUTLINE_SIZE, sf::Vector2f(posX, posY));
			posX += CASE_SIZE;
		}

		posX = 5;
		posY += CASE_SIZE;
	}

	// Setup Start&End
	m_vStart.first = GRID_SIZE / 2;
	m_vStart.second = std::max(GRID_SIZE / 2 - 5, 0);
	m_aaGrid[m_vStart.first][m_vStart.second].SetState(ECaseState::Start);

	m_vEnd.first = GRID_SIZE / 2;
	m_vEnd.second= std::min(GRID_SIZE / 2 + 5, GRID_SIZE - 1);
	m_aaGrid[m_vEnd.first][m_vEnd.second].SetState(ECaseState::End);

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

void Grid::Reset(void)
{
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			m_aaGrid[i][j].SetState(ECaseState::Empty, true);
		}
	}

	m_aaGrid[GRID_SIZE / 2][GRID_SIZE / 2 - 5].SetState(ECaseState::Start);
	m_aaGrid[GRID_SIZE / 2][GRID_SIZE / 2 + 5].SetState(ECaseState::End);
}

// Used to mark treated cases during alogirthms execution
void Grid::SetCaseColor(const std::pair<int, int>& vCase, const sf::Color& color)
{
	m_aaGrid[vCase.first][vCase.second].SetColor(color);
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
	int x = posY / CASE_SIZE;
	int y = posX / CASE_SIZE;

	if (!IsValidID(x, y))
		return;

	if (ECaseState::Start == m_eStateToApply)
	{
		if (ECaseState::End == m_aaGrid[x][y].GetState())
			return;

		m_aaGrid[m_vStart.first][m_vStart.second].SetState(ECaseState::Empty, true);
		m_vStart.first = x;
		m_vStart.second = y;
	}
		
	if (ECaseState::End == m_eStateToApply)
	{
		if (ECaseState::Start == m_aaGrid[x][y].GetState())
			return;

		m_aaGrid[m_vEnd.first][m_vEnd.second].SetState(ECaseState::Empty, true);
		m_vEnd.first = x;
		m_vEnd.second = y;
	}

	m_aaGrid[x][y].SetState(m_eStateToApply);
}

void Grid::OnMouseReleased(void)
{
	m_eStateToApply = ECaseState::Empty;
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
	return m_aaGrid[x][y].GetState() != ECaseState::Wall && IsValidID(x, y);
}
