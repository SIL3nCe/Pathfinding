#include "Dijkstra.h"

using namespace std;

// https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm

std::vector<std::pair<int, int>>& Dijkstra::Execute(const GridWorker& Grid, bool bUseDiagonal)
{
	vector<pair<int, int>> aQueue;

	for (int i = 0; i < Grid.GetHeight(); ++i)
	{
		vector<SDatas> aLine(Grid.GetWidth());
		for (int j = 0; j < Grid.GetWidth(); ++j)
		{
			SDatas datas({ static_cast<float>(UINT_MAX - 1), {-1, -1} });
			aLine.push_back(datas);
			aQueue.push_back({ i, j });
		}
		m_aaWorker.push_back(aLine);
	}

	m_vCurrentNode = Grid.GetStart();
	m_aaWorker[m_vCurrentNode.first][m_vCurrentNode.second].fDistance = 0.0f;

	while (aQueue.size() != 0)
	{
		// Get min dist node in queue
		ComputeMinDistNodeInQueue(aQueue);

		if (m_vCurrentNode == Grid.GetEnd() // Current is end of path
			|| m_vCurrentNode.first == -1 // Unreachable (no more node to visit)
			)
		{
			break;
		}

		// Get its neihbours
		Grid.ComputeNeighboursOfCurrent(m_vCurrentNode, bUseDiagonal, m_aNeighbours);

		// Compute distance to those neighbours
		int nNeighbours = m_aNeighbours.size();
		for (int i = 0; i < nNeighbours; ++i)
		{
			const pair<int, int>& vNode = m_aNeighbours[i];

			if (aQueue.end() == find(aQueue.begin(), aQueue.end(), vNode))
				continue;

			// Update dist
			float fAdd = (vNode.first == m_vCurrentNode.first || vNode.second == m_vCurrentNode.second) ? 1.0f : sqrt(2);
			float newDist = m_aaWorker[m_vCurrentNode.first][m_vCurrentNode.second].fDistance + fAdd;

			// Special case with diagonale, do not override cheapest dist
			if (bUseDiagonal && newDist > m_aaWorker[vNode.first][vNode.second].fDistance)
				continue;

			m_aaWorker[vNode.first][vNode.second].fDistance = newDist;

			// Update prev
			m_aaWorker[vNode.first][vNode.second].vPrevious = m_vCurrentNode;

			//m_pGrid->SetCaseColor(vNode, sf::Color::Yellow);
		}

		//m_pGrid->SetCaseColor(m_vCurrentNode, sf::Color::Cyan);
	}

	// Construct and return path
	m_aFinalPath.clear();

	m_aFinalPath.push_back(Grid.GetEnd());
	while (m_vCurrentNode.first != -1)
	{
		m_vCurrentNode = m_aaWorker[m_vCurrentNode.first][m_vCurrentNode.second].vPrevious;
		m_aFinalPath.push_back(m_vCurrentNode);
	}

	return m_aFinalPath;
}

/*
void Dijkstra::DrawGui()
{
	m_bGuiOpen = false;

	ImGui::PushID("Dijkstra");
	if (ImGui::CollapsingHeader("Dijkstra"))
	{
		m_bGuiOpen = true;

		ImGui::Checkbox("Use Diagonal", &m_bUseDiagonal);
		ImGui::Checkbox("Bidirectional", &m_bBidirectional);

		ImGui::Separator();

		ImGui::Checkbox("Distances text", &m_bDrawDebugTexts);
	}
	ImGui::PopID();
}
*/

void Dijkstra::ComputeMinDistNodeInQueue(vector<pair<int, int>> & aQueue)
{
	float currDist = UINT_MAX;
	int id = -1;

	int nNode = aQueue.size();
	for (int i = 0; i < nNode; ++i)
	{
		float fNodeDist = m_aaWorker[aQueue[i].first][aQueue[i].second].fDistance;
		if (fNodeDist < currDist)
		{
			id = i;
			currDist = fNodeDist;
		}
	}

	if (id > -1)
	{
		m_vCurrentNode = aQueue[id];
		aQueue.erase(aQueue.begin() + id);
	}
	else
	{
		m_vCurrentNode.first = -1;
	}
}
