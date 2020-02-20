#include "BreadthFirst.h"

using namespace std;

// https://en.wikipedia.org/wiki/Breadth-first_search

void BreadthFirst::Start(void)
{
	Pathfinding::Start();

	m_aNodeQueue = {}; // Queue clear

	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			m_aaWorker[i][j].bDiscovered = false;
			m_aaWorker[i][j].vParent = { -1, -1 };
		}
	}

	const pair<int, int>& vStart = m_pGrid->GetStart();
	m_aNodeQueue.push(vStart);
	m_aaWorker[vStart.first][vStart.second].bDiscovered = true;

	m_bUseDiagonal = false;
	m_bBidirectional = false;
}

bool BreadthFirst::Execute(void)
{
	// Unreachable
	if (m_aNodeQueue.empty())
	{
		m_vCurrentNode.first = -1;
		return false;
	}

	m_vCurrentNode = m_aNodeQueue.front();
	m_aNodeQueue.pop();
	
	// Current is end of path
	if (m_vCurrentNode == m_pGrid->GetEnd())
		return false;

	m_steps++;

	// Get its neihbours
	ComputeNeighboursOfCurrent();

	// Compute distance to those neighbours
	int nNeighbours = m_aNeighbours.size();
	for (int i = 0; i < nNeighbours; ++i)
	{
		const pair<int, int>& vNode = m_aNeighbours[i];

		if (!m_aaWorker[vNode.first][vNode.second].bDiscovered) 
		{
			// Mark as discovered
			m_aaWorker[vNode.first][vNode.second].bDiscovered = true;

			// Update prev
			m_aaWorker[vNode.first][vNode.second].vParent = m_vCurrentNode;

			// Enqueue node
			m_aNodeQueue.push(vNode);

			m_pGrid->SetCaseColor(vNode, sf::Color::Yellow); // Discovered and in queue
		}
	}

	m_pGrid->SetCaseColor(m_vCurrentNode, sf::Color::Cyan); // Discovered and no more in queue
	
	return true;
}

void BreadthFirst::Stop(void)
{
	while (m_vCurrentNode.first != -1)
	{
		sf::Vector2f vLocation;
		if (m_pGrid->GetScreenCoordFromCell(m_vCurrentNode, vLocation))
		{
			m_aPath.push_back(sf::Vertex(vLocation, sf::Color::Magenta));
		}
		m_vCurrentNode = m_aaWorker[m_vCurrentNode.first][m_vCurrentNode.second].vParent;
	}

	m_fLength = m_aPath.size(); // TODO handle diagonals length

	Pathfinding::Stop();
}

void BreadthFirst::DrawGui(void)
{
	m_bGuiOpen = false;
	if (ImGui::CollapsingHeader("Breadth First"))
	{
		m_bGuiOpen = true;

		ImGui::Checkbox("Use Diagonal", &m_bUseDiagonal);
		ImGui::Checkbox("Bidirectional", &m_bBidirectional);
	}
}

void BreadthFirst::Draw(sf::RenderWindow& window)
{
	if (!m_aPath.empty())
	{
		window.draw(&m_aPath[0], m_aPath.size(), sf::LineStrip);
	}
}

void BreadthFirst::Clear(void)
{
	m_aPath.clear();
}

void BreadthFirst::ComputeNeighboursOfCurrent(void)
{
	m_aNeighbours.clear();

	pair<int, int> vTestNode = m_vCurrentNode;

	// Up
	vTestNode.first -= 1;
	if (m_pGrid->IsWalkable(vTestNode))
	{
		m_aNeighbours.push_back(vTestNode);
	}

	// Right
	vTestNode.first += 1;
	vTestNode.second += 1;
	if (m_pGrid->IsWalkable(vTestNode))
	{
		m_aNeighbours.push_back(vTestNode);
	}

	// Down
	vTestNode.first += 1;
	vTestNode.second -= 1;
	if (m_pGrid->IsWalkable(vTestNode))
	{
		m_aNeighbours.push_back(vTestNode);
	}

	// Left
	vTestNode.first -= 1;
	vTestNode.second -= 1;
	if (m_pGrid->IsWalkable(vTestNode))
	{
		m_aNeighbours.push_back(vTestNode);
	}
}
