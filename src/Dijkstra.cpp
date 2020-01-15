#include "Dijkstra.h"

void Dijkstra::Initialize(Grid& grid)
{
	Pathfinding::Initialize(grid);

	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; i < GRID_SIZE; ++j)
		{
			m_aaWorker[i][j].bVisited = false;
			m_aaWorker[i][j].distance = INT_MAX;
		}
	}

	m_vCurrentNode = grid.GetStart();
	m_aNodeQueue.push_back(m_vCurrentNode);
	m_aaWorker[m_vCurrentNode.first][m_vCurrentNode.second].distance = 0;
}

// https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
void Dijkstra::Execute(void)
{
	std::vector<std::pair<int, int>> aNeighbours;

	while (true)
	{
		// Get min dist node in queue
		ComputeMinDistNodeInQueue();

		// Abort if current is end of path
		if (m_vCurrentNode == m_pGrid->GetEnd())
			break;

		// Get its neihbours
		ComputeNeighboursOfCurrent(aNeighbours);

		// Compute distance to those neighbours
		int nNeighbours = m_aNodeQueue.size();
		for (int i = 0; i < nNeighbours; ++i)
		{
			m_aaWorker[aNeighbours[i].first][aNeighbours[i].second].distance = m_aaWorker[m_vCurrentNode.first][m_vCurrentNode.second].distance + 1;

			m_aNodeQueue.push_back(aNeighbours[i]);
		}

		m_aaWorker[m_vCurrentNode.first][m_vCurrentNode.second].bVisited = true;
	}

	// Compute and draw final path from m_vCurrentNode to start


}

void Dijkstra::ComputeMinDistNodeInQueue(void)
{
	int currDist = INT_MAX;
	int id = -1;

	int nNode = m_aNodeQueue.size();
	for (int i = 0; i < nNode; ++i)
	{
		if (m_aaWorker[m_vCurrentNode.first][m_vCurrentNode.second].distance < currDist)
		{
			id = i;
			currDist = m_aaWorker[m_vCurrentNode.first][m_vCurrentNode.second].distance;
		}
	}

	m_vCurrentNode = m_aNodeQueue[id];
	m_aNodeQueue.erase(m_aNodeQueue.begin() + id);
}

void Dijkstra::ComputeNeighboursOfCurrent(std::vector<std::pair<int, int>> & aNeighbours)
{
	aNeighbours.clear();

	std::pair<int, int> vTestNode = m_vCurrentNode;

	// Up
	vTestNode.first -= 1;
	if (m_pGrid->IsValidID(vTestNode) && !m_aaWorker[vTestNode.first][vTestNode.second].bVisited)
	{
		aNeighbours.push_back(vTestNode);
	}

	// Right
	vTestNode.first += 1;
	vTestNode.second += 1;
	if (m_pGrid->IsValidID(vTestNode) && !m_aaWorker[vTestNode.first][vTestNode.second].bVisited)
	{
		aNeighbours.push_back(vTestNode);
	}

	// Down
	vTestNode.first -= 1;
	vTestNode.second -= 1;
	if (m_pGrid->IsValidID(vTestNode) && !m_aaWorker[vTestNode.first][vTestNode.second].bVisited)
	{
		aNeighbours.push_back(vTestNode);
	}

	// Left
	vTestNode.first += 1;
	vTestNode.second -= 1;
	if (m_pGrid->IsValidID(vTestNode) && !m_aaWorker[vTestNode.first][vTestNode.second].bVisited)
	{
		aNeighbours.push_back(vTestNode);
	}
}
