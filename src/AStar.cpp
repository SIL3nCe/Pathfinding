#include "AStar.h"

using namespace std;

// https://en.wikipedia.org/wiki/A*_search_algorithm

void AStar::Initialize(Grid& grid, sf::Font& font)
{
	Pathfinding::Initialize(grid, font);

	sf::Vector2f vLocation;
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			if (m_pGrid->GetScreenCoordFromCell(i, j, vLocation))
			{
				m_aTexts[i * GRID_SIZE + j].setFont(*m_pFont);
				m_aTexts[i * GRID_SIZE + j].setString("-");
				m_aTexts[i * GRID_SIZE + j].setColor(sf::Color::Black);
				m_aTexts[i * GRID_SIZE + j].setPosition({ vLocation.x - CELL_SIZE * 0.25f, vLocation.y - CELL_SIZE * 0.25f });
				m_aTexts[i * GRID_SIZE + j].setCharacterSize(CELL_SIZE * 0.5);
			}
		}
	}
}

void AStar::Start(void)
{
	m_aNodeQueue = {}; // Queue clear

	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			m_aaWorker[i][j].bDiscovered = false;
			m_aaWorker[i][j].cost = -1;
			pair<int, int> vNode(i, j);
			m_aaWorker[i][j].heuristique = Utility::GetManhattanDistance(vNode, m_pGrid->GetEnd());

			char strNum[10];
			sprintf(strNum, "%i", m_aaWorker[i][j].heuristique);
			m_aTexts[i * GRID_SIZE + j].setString(strNum);

			m_aaWorker[i][j].vPrevious = { -1, -1 };
		}
	}

	const pair<int, int>& vStart = m_pGrid->GetStart();
	m_aNodeQueue.push_back(vStart);
	m_aaWorker[vStart.first][vStart.second].bDiscovered = true;
	m_aaWorker[vStart.first][vStart.second].cost = 0;
	
	m_bDrawDebugTexts = true;
}

bool AStar::Execute(void)
{
	ComputeMinHeuristiqueNodeInQueue();
	
	if (m_vCurrentNode == m_pGrid->GetEnd() // Current is end of path
		|| m_vCurrentNode.first == -1 // Unreachable (no more node to visit)
		)
	{
		return false;
	}

	// Get its neihbours
	ComputeNeighboursOfCurrent();

	// Compute distance to those neighbours
	int nNeighbours = m_aNeighbours.size();
	for (int i = 0; i < nNeighbours; ++i)
	{
		const pair<int, int>& vNode = m_aNeighbours[i];

		//TODO
	}

	return true;
}

void AStar::Stop(void)
{
	while (m_vCurrentNode.first != -1)
	{
		sf::Vector2f vLocation;
		if (m_pGrid->GetScreenCoordFromCell(m_vCurrentNode, vLocation))
		{
			m_aPath.push_back(sf::Vertex(vLocation, sf::Color::Magenta));
		}
		m_vCurrentNode = m_aaWorker[m_vCurrentNode.first][m_vCurrentNode.second].vPrevious;
	}
}

void AStar::Draw(sf::RenderWindow& window)
{
	if (!m_aPath.empty())
	{
		window.draw(&m_aPath[0], m_aPath.size(), sf::LineStrip);
	}

	if (m_bDrawDebugTexts)
	{
		int nTexts = GRID_SIZE * GRID_SIZE;
		for (int i = 0; i < nTexts; ++i)
		{
			window.draw(m_aTexts[i]);
		}
	}
}

void AStar::Clear(void)
{
	m_aPath.clear();
	m_bDrawDebugTexts = false;
	m_aNodeQueue.clear();
}

void AStar::ComputeMinHeuristiqueNodeInQueue(void)
{
	int currDist = INT_MAX;
	int id = -1;

	int nNode = m_aNodeQueue.size();
	for (int i = 0; i < nNode; ++i)
	{
		float fNodeDist = m_aaWorker[m_aNodeQueue[i].first][m_aNodeQueue[i].second].heuristique;
		if (fNodeDist < currDist)
		{
			id = i;
			currDist = fNodeDist;
		}
	}

	if (id > -1)
	{
		m_vCurrentNode = m_aNodeQueue[id];
		m_aNodeQueue.erase(m_aNodeQueue.begin() + id);
	}
	else
	{
		m_vCurrentNode.first = -1;
	}
}

void AStar::ComputeNeighboursOfCurrent(void)
{
	m_aNeighbours.clear();

	pair<int, int> vTestNode = m_vCurrentNode;

	// Up
	vTestNode.first -= 1;
	if (m_pGrid->IsWalkable(vTestNode) && m_aNodeQueue.end() != find(m_aNodeQueue.begin(), m_aNodeQueue.end(), vTestNode))
	{
		m_aNeighbours.push_back(vTestNode);
	}

	// Right
	vTestNode.first += 1;
	vTestNode.second += 1;
	if (m_pGrid->IsWalkable(vTestNode) && m_aNodeQueue.end() != find(m_aNodeQueue.begin(), m_aNodeQueue.end(), vTestNode))
	{
		m_aNeighbours.push_back(vTestNode);
	}

	// Down
	vTestNode.first += 1;
	vTestNode.second -= 1;
	if (m_pGrid->IsWalkable(vTestNode) && m_aNodeQueue.end() != find(m_aNodeQueue.begin(), m_aNodeQueue.end(), vTestNode))
	{
		m_aNeighbours.push_back(vTestNode);
	}

	// Left
	vTestNode.first -= 1;
	vTestNode.second -= 1;
	if (m_pGrid->IsWalkable(vTestNode) && m_aNodeQueue.end() != find(m_aNodeQueue.begin(), m_aNodeQueue.end(), vTestNode))
	{
		m_aNeighbours.push_back(vTestNode);
	}
}
