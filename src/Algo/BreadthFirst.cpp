#include "BreadthFirst.h"

using namespace std;

// https://en.wikipedia.org/wiki/Breadth-first_search

std::vector<std::pair<int, int>>& BreadthFirst::Execute(const GridWorker& Grid, bool bUseDiagonal)
{
	queue<pair<int, int>> aQueue;

	for (int i = 0; i < Grid.GetHeight(); ++i)
	{
		vector<SDatas> aLine(Grid.GetWidth());
		for (int j = 0; j < Grid.GetWidth(); ++j)
		{
			SDatas datas({ false, {-1, -1} });
			aLine.push_back(datas);
		}
		m_aaWorker.push_back(aLine);
	}

	const pair<int, int>& vStart = Grid.GetStart();
	aQueue.push(vStart);
	m_aaWorker[vStart.first][vStart.second].bDiscovered = true;

	while (true)
	{
		// Unreachable
		if (aQueue.empty())
		{
			m_vCurrentNode.first = -1;
			break;
		}

		m_vCurrentNode = aQueue.front();
		aQueue.pop();

		// Current is end of path
		if (m_vCurrentNode == Grid.GetEnd())
			break;

		// Get its neihbours
		Grid.ComputeNeighboursOfCurrent(m_vCurrentNode, bUseDiagonal, m_aNeighbours);

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
				aQueue.push(vNode);

				//m_pGrid->SetCaseColor(vNode, sf::Color::Yellow); // Discovered and in queue
			}
		}

		//m_pGrid->SetCaseColor(m_vCurrentNode, sf::Color::Cyan); // Discovered and no more in queue
	}

	// Construct and return path
	m_aFinalPath.clear();

	m_aFinalPath.push_back(Grid.GetEnd());
	while (m_vCurrentNode.first != -1)
	{
		m_vCurrentNode = m_aaWorker[m_vCurrentNode.first][m_vCurrentNode.second].vParent;
		m_aFinalPath.push_back(m_vCurrentNode);
	}

	return m_aFinalPath;
}
/*
void BreadthFirst::DrawGui()
{
	m_bGuiOpen = false;

	ImGui::PushID("Breadth First");
	if (ImGui::CollapsingHeader("Breadth First"))
	{
		m_bGuiOpen = true;

		ImGui::Checkbox("Use Diagonal", &m_bUseDiagonal);
		ImGui::Checkbox("Bidirectional", &m_bBidirectional);
	}
	ImGui::PopID();
}
*/
