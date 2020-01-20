#include "Dijkstra.h"

using namespace std;

// https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm

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
		}
	}

	m_vCurrentNode = m_pGrid->GetStart();
	m_aaWorker[m_vCurrentNode.first][m_vCurrentNode.second].distance = 0;
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
		// Update dist
		m_aaWorker[m_aNeighbours[i].first][m_aNeighbours[i].second].distance = m_aaWorker[m_vCurrentNode.first][m_vCurrentNode.second].distance + 1;
		// Update prev
		m_aaWorker[m_aNeighbours[i].first][m_aNeighbours[i].second].vPrevious = m_vCurrentNode;
		m_pGrid->SetCaseColor(m_aNeighbours[i], sf::Color::Yellow);
	}

	m_pGrid->SetCaseColor(m_vCurrentNode, sf::Color::Cyan);

	return true;
}

// Compute and draw final path from m_vCurrentNode to start
void Dijkstra::Stop(void)
{
	while (m_vCurrentNode.first != -1)
	{
		m_pGrid->SetCaseColor(m_vCurrentNode, sf::Color::Magenta);
		m_vCurrentNode = m_aaWorker[m_vCurrentNode.first][m_vCurrentNode.second].vPrevious;
		//TODO add vertex to m_aPath, get screen coord from cell coord
	}
}

void Dijkstra::Draw(sf::RenderWindow& window)
{
	window.draw(m_aPath);
	//TODO draw distances in each cases
}

void Dijkstra::Clear(void)
{
	m_aPath.clear();
	//TODO clear distances
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
