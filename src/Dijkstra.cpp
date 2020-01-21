#include "Dijkstra.h"

using namespace std;

// https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm

void Dijkstra::Initialize(Grid& grid, sf::Font& font)
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

// Init algo datas
void Dijkstra::Start(void)
{
	m_aNodeQueue.clear();
	m_aNeighbours.clear();

	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			m_aaWorker[i][j].distance = INT_MAX;
			m_aaWorker[i][j].vPrevious = {-1, -1};
			m_aNodeQueue.push_back({i, j});

			m_aTexts[i * GRID_SIZE + j].setString("-");
		}
	}

	m_vCurrentNode = m_pGrid->GetStart();
	m_aaWorker[m_vCurrentNode.first][m_vCurrentNode.second].distance = 0;

	m_bDrawDebugTexts = true;
}

// Async exec
bool Dijkstra::Execute(void)
{
	// Get min dist node in queue
	ComputeMinDistNodeInQueue();

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
		const std::pair<int, int>& vNode = m_aNeighbours[i];

		// Update dist
		int newDist = m_aaWorker[m_vCurrentNode.first][m_vCurrentNode.second].distance + 1;
		m_aaWorker[vNode.first][vNode.second].distance = newDist;
		
		// Update prev
		m_aaWorker[vNode.first][vNode.second].vPrevious = m_vCurrentNode;
		
		// Update text
		char strNum[10];
		sprintf(strNum, "%i", newDist);
		m_aTexts[vNode.first * GRID_SIZE + vNode.second].setString(strNum);

		m_pGrid->SetCaseColor(vNode, sf::Color::Yellow);
	}

	m_pGrid->SetCaseColor(m_vCurrentNode, sf::Color::Cyan);

	return true;
}

// Compute and draw final path from m_vCurrentNode to start
void Dijkstra::Stop(void)
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

void Dijkstra::Draw(sf::RenderWindow& window)
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

void Dijkstra::Clear(void)
{
	m_aPath.clear();
	m_bDrawDebugTexts = false;
	m_aNodeQueue.clear();
}

void Dijkstra::ComputeMinDistNodeInQueue(void)
{
	int currDist = INT_MAX;
	int id = -1;

	int nNode = m_aNodeQueue.size();
	for (int i = 0; i < nNode; ++i)
	{
		float fNodeDist = m_aaWorker[m_aNodeQueue[i].first][m_aNodeQueue[i].second].distance;
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

void Dijkstra::ComputeNeighboursOfCurrent(void)
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
