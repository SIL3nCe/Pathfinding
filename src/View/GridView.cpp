#include "GridView.h"
#include "GridWorker.h"

GridView::GridView()
: m_eStateToApply(ECellState::Empty)
, m_bDrawPath(false)
, m_aPath()
{
	int posX = 0, posY = 0;
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			m_aaGrid[i][j].Initialize(CELL_SIZE, CELL_OUTLINE_SIZE, sf::Vector2f(posX, posY));
			posX += CELL_SIZE;
		}

		posX = 0;
		posY += CELL_SIZE;
	}

	// Setup Start&End
	m_vStart.first = GRID_SIZE / 2;
	m_vStart.second = std::max(GRID_SIZE / 2 - 5, 0);
	m_aaGrid[m_vStart.first][m_vStart.second].SetState(ECellState::Start);

	m_vEnd.first = GRID_SIZE / 2;
	m_vEnd.second= std::min(GRID_SIZE / 2 + 5, GRID_SIZE - 1);
	m_aaGrid[m_vEnd.first][m_vEnd.second].SetState(ECellState::End);
}

void GridView::Draw(sf::RenderWindow & window)
{
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			m_aaGrid[i][j].Draw(window);
		}
	}

	if (m_bDrawPath && !m_aPath.empty())
	{
		window.draw(&m_aPath[0], m_aPath.size(), sf::LineStrip);
	}
}

void GridView::Clear()
{
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			m_aaGrid[i][j].SetState(ECellState::Empty);
		}
	}

	m_bDrawPath = false;
}

void GridView::ClearDebugInfo()
{
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			if (ECellState::Wall != m_aaGrid[i][j].GetState())
			{
				m_aaGrid[i][j].ClearDebugInfo();
			}
		}
	}

	m_bDrawPath = false;
}

void GridView::Reset()
{
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			m_aaGrid[i][j].SetState(ECellState::Empty, true);
		}
	}

	m_bDrawPath = false;
	m_aPath.clear();

	// Setup Start&End
	m_vStart.first = GRID_SIZE / 2;
	m_vStart.second = std::max(GRID_SIZE / 2 - 5, 0);
	m_aaGrid[m_vStart.first][m_vStart.second].SetState(ECellState::Start);

	m_vEnd.first = GRID_SIZE / 2;
	m_vEnd.second = std::min(GRID_SIZE / 2 + 5, GRID_SIZE - 1);
	m_aaGrid[m_vEnd.first][m_vEnd.second].SetState(ECellState::End);
}

void GridView::FillGridWorker(GridWorker * grid)
{
	std::vector<std::vector<bool>>& workerGrid = grid->GetGridToFill();
	
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			workerGrid[i][j] = m_aaGrid[i][j].GetState() != ECellState::Wall;
		}
	}
}

float GridView::DrawPath(const std::vector<std::pair<int, int>>& aPath)
{
	float fLength = 0.0f;
	m_aPath.clear();

	int nNodes = aPath.size();
	for (int i = 0; i < nNodes; ++i)
	{
		sf::Vector2f vLocation;
		if (GetScreenCoordFromCell(aPath[i], vLocation))
		{
			m_aPath.push_back(sf::Vertex(vLocation, sf::Color::Magenta));
		}

		if (i > 0)
		{
			fLength += (aPath[i].first == aPath[i - 1].first || aPath[i].second == aPath[i - 1].second) ? 1.0f : SquareRootOf2;
		}
	}

	m_bDrawPath = true;
	
	return fLength;
}

void GridView::SetDrawPath(bool bDraw)
{
	m_bDrawPath = bDraw;
}

void GridView::DoOperation(const SOperation& operation)
{
	if (!IsValidID(operation.vCellCoord.first, operation.vCellCoord.second))
		return;

	m_aaGrid[operation.vCellCoord.first][operation.vCellCoord.second].DoOperation(operation.eOperation);
}

void GridView::UndoOperation(const SOperation& operation)
{
	if (!IsValidID(operation.vCellCoord.first, operation.vCellCoord.second))
		return;

	m_aaGrid[operation.vCellCoord.first][operation.vCellCoord.second].UndoOperation();
}

void GridView::OnMouseClicked(int posX, int posY)
{
	int x = posY / CELL_SIZE;
	int y = posX / CELL_SIZE;

	if (!IsValidID(x, y))
		return;

	m_eStateToApply = m_aaGrid[x][y].GetState();

	if (ECellState::Wall == m_eStateToApply)
		m_eStateToApply = ECellState::Empty;
	else if (ECellState::Empty == m_eStateToApply)
		m_eStateToApply = ECellState::Wall;

	m_aaGrid[x][y].SetState(m_eStateToApply);
}

void GridView::OnMouseMoved(int posX, int posY)
{
	int x = posY / CELL_SIZE;
	int y = posX / CELL_SIZE;

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

void GridView::OnMouseReleased()
{
	m_eStateToApply = ECellState::Empty;
}

bool GridView::GetScreenCoordFromCell(int x, int y, sf::Vector2f& vLocation) const
{
	if (IsValidID(x, y))
	{
		vLocation = m_aaGrid[x][y].GetScreenCoord();
		return true;
	}

	return false;
}

bool GridView::GetScreenCoordFromCell(const std::pair<int, int>& vNode, sf::Vector2f& vLocation) const
{
	return GetScreenCoordFromCell(vNode.first, vNode.second, vLocation);
}

inline bool GridView::IsValidID(int x, int y) const
{
	return (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE);
}
