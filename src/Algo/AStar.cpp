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

	m_eHeuristic = EHeuristics::Manhattan;
	m_bUseDiagonal = false;
	m_bBidirectional = false;
	m_bDrawDebugTexts = true;
}

void AStar::Start(void)
{
	m_aNodeQueue = {}; // Queue clear

	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			m_aaWorker[i][j].bClosed = false;
			m_aaWorker[i][j].cost = INT_MAX;
			m_aaWorker[i][j].heuristique = ComputeHeuristic({i, j}, m_pGrid->GetEnd());

			char strNum[10];
			sprintf(strNum, "%i", m_aaWorker[i][j].heuristique);
			m_aTexts[i * GRID_SIZE + j].setString(strNum);

			m_aaWorker[i][j].vPrevious = { -1, -1 };
		}
	}

	const pair<int, int>& vStart = m_pGrid->GetStart();
	m_aNodeQueue.push_back(vStart);
	m_aaWorker[vStart.first][vStart.second].bClosed = true;
	m_aaWorker[vStart.first][vStart.second].cost = 0;
}

bool AStar::Execute(void)
{
	ComputeMinHeuristicNodeInQueue();
	
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

		int newCost = m_aaWorker[m_vCurrentNode.first][m_vCurrentNode.second].cost + 1;

		SDatas * pData = &m_aaWorker[vNode.first][vNode.second];

		if (!pData->bClosed && newCost < pData->cost)
		{
			pData->vPrevious = m_vCurrentNode;
			pData->cost = newCost;
			pData->heuristique = pData->cost + ComputeHeuristic(vNode, m_pGrid->GetEnd());
			
			m_aNodeQueue.push_back(vNode);
			m_pGrid->SetCaseColor(vNode, sf::Color::Yellow);
		}
	}

	m_aaWorker[m_vCurrentNode.first][m_vCurrentNode.second].bClosed = true;
	m_pGrid->SetCaseColor(m_vCurrentNode, sf::Color::Cyan);

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

void AStar::DrawGui(void)
{
	if (ImGui::CollapsingHeader("A*"))
	{
		if (ImGui::RadioButton("Manhattan", m_eHeuristic == EHeuristics::Manhattan)) { m_eHeuristic = EHeuristics::Manhattan; }
		if (ImGui::RadioButton("Euclidean", m_eHeuristic == EHeuristics::Euclidean)) { m_eHeuristic = EHeuristics::Euclidean; }
		if (ImGui::RadioButton("Chebyshev", m_eHeuristic == EHeuristics::Chebyshev)) { m_eHeuristic = EHeuristics::Chebyshev; }
		if (ImGui::RadioButton("Null (Dijkstra)", m_eHeuristic == EHeuristics::Null)) { m_eHeuristic = EHeuristics::Null; }
	
		ImGui::Separator();
	
		ImGui::Checkbox("Use Diagonal", &m_bUseDiagonal);
		ImGui::Checkbox("Bidirectional", &m_bBidirectional);
	
		ImGui::Checkbox("Heuristique value text", &m_bDrawDebugTexts);
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

void AStar::ComputeMinHeuristicNodeInQueue(void)
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

	if (m_bUseDiagonal)
	{
		// Top Left
		vTestNode.first -= 1;
		if (m_pGrid->IsWalkable(vTestNode))
		{
			m_aNeighbours.push_back(vTestNode);
		}

		// Top Right
		vTestNode.second += 2;
		if (m_pGrid->IsWalkable(vTestNode))
		{
			m_aNeighbours.push_back(vTestNode);
		}

		// Bottom Right
		vTestNode.first += 2;
		if (m_pGrid->IsWalkable(vTestNode))
		{
			m_aNeighbours.push_back(vTestNode);
		}

		// Bottom Left
		vTestNode.second -= 2;
		if (m_pGrid->IsWalkable(vTestNode))
		{
			m_aNeighbours.push_back(vTestNode);
		}
	}
}

float AStar::ComputeHeuristic(const std::pair<int, int>& start, const std::pair<int, int>& end)
{
	switch (m_eHeuristic)
	{
		case EHeuristics::Manhattan: { return Utility::GetManhattanDistance(start, end); };
		case EHeuristics::Euclidean: { return Utility::GetEuclideanDistance(start, end); };
		case EHeuristics::Chebyshev: {return Utility::GetChebyshevDistance(start, end); };
		case EHeuristics::Null: { return 0; };
	}

	return 0;
}
