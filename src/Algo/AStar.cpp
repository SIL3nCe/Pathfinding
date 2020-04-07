#include "AStar.h"
#include <queue>

using namespace std;

// https://en.wikipedia.org/wiki/A*_search_algorithm

vector<pair<int, int>>& AStar::Execute(const GridWorker& Grid, bool bUseDiagonal, EHeuristic eHeuristic, float fWeight, void(*OnDoingOperation)(EOperations, const pair<int, int>&) /*= DefaultOnDoingOperation*/)
{
	vector<vector<SDatas>> aaWorker; //TODO Find a better way

	auto compare = [&](pair<int, int> & left, pair<int, int> & right)
	{
		return aaWorker[left.first][left.second].heuristique > aaWorker[right.first][right.second].heuristique;
	};

	priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> aPrioQueue(compare);
	
	for (int i = 0; i < Grid.GetHeight(); ++i)
	{
		vector<SDatas> aLine(Grid.GetWidth());
		for (int j = 0; j < Grid.GetWidth(); ++j)
		{
			SDatas datas({ false, INT_MAX, static_cast<float>(UINT_MAX), {-1, -1} });
			aLine[j] = datas;
		}
		aaWorker.push_back(aLine);
	}

	const pair<int, int>& vStart = Grid.GetStart();
	aPrioQueue.push(vStart);
	aaWorker[vStart.first][vStart.second].bClosed = true;
	aaWorker[vStart.first][vStart.second].cost = 0.0f;
	aaWorker[vStart.first][vStart.second].heuristique = ComputeHeuristic(vStart, Grid.GetEnd(), eHeuristic, fWeight);

	pair<int, int> vCurrentNode;

	while (aPrioQueue.size() != 0)
	{
		vCurrentNode = aPrioQueue.top();
		aPrioQueue.pop();

		if (vCurrentNode == Grid.GetEnd() // Current is end of path
			|| vCurrentNode.first == -1 // Unreachable (no more node to visit)
			)
		{
			break;
		}

		// Get its neihbours
		Grid.ComputeNeighboursOfCurrent(vCurrentNode, bUseDiagonal, m_aNeighbours);

		// Compute distance to those neighbours
		int nNeighbours = m_aNeighbours.size();
		for (int i = 0; i < nNeighbours; ++i)
		{
			const pair<int, int>& vNode = m_aNeighbours[i];

			float fAdd = (vNode.first == vCurrentNode.first || vNode.second == vCurrentNode.second) ? 1.0f : sqrt(2);
			float newCost = aaWorker[vCurrentNode.first][vCurrentNode.second].cost + fAdd;

			SDatas* pData = &aaWorker[vNode.first][vNode.second];

			if (!pData->bClosed && newCost < pData->cost)
			{
				pData->vPrevious = vCurrentNode;
				pData->cost = newCost;
				pData->heuristique = pData->cost + ComputeHeuristic(vNode, Grid.GetEnd(), eHeuristic, fWeight);

				aPrioQueue.push(vNode);
				OnDoingOperation(EOperations::QueuedNode, vNode);
			}
		}

		aaWorker[vCurrentNode.first][vCurrentNode.second].bClosed = true;
		OnDoingOperation(EOperations::ClosedNode, vCurrentNode);
	}

	// Construct and return path
	m_aFinalPath.clear();
	
	m_aFinalPath.push_back(Grid.GetEnd());
	while (vCurrentNode.first != -1)
	{
		vCurrentNode = aaWorker[vCurrentNode.first][vCurrentNode.second].vPrevious;
		m_aFinalPath.push_back(vCurrentNode);
	}

	return m_aFinalPath;
}

/*
void AStar::DrawGui()
{
	m_bGuiOpen = false;

	ImGui::PushID("A*");
	if (ImGui::CollapsingHeader("A*", ImGuiTreeNodeFlags_DefaultOpen))
	{
		m_bGuiOpen = true;

		if (ImGui::RadioButton("Manhattan", m_eHeuristic == EHeuristics::Manhattan)) { m_eHeuristic = EHeuristics::Manhattan; }
		if (ImGui::RadioButton("Euclidean", m_eHeuristic == EHeuristics::Euclidean)) { m_eHeuristic = EHeuristics::Euclidean; }
		if (ImGui::RadioButton("Chebyshev", m_eHeuristic == EHeuristics::Chebyshev)) { m_eHeuristic = EHeuristics::Chebyshev; }
		if (ImGui::RadioButton("Null (Dijkstra)", m_eHeuristic == EHeuristics::Null)) { m_eHeuristic = EHeuristics::Null; }
	
		ImGui::Separator();
	
		ImGui::Checkbox("Use Diagonal", &m_bUseDiagonal);
		ImGui::Checkbox("Bidirectional", &m_bBidirectional);
		ImGui::InputFloat("Weight", &m_fWeight, 1.0f, 10.0f, 2, ImGuiInputTextFlags_AutoSelectAll);	
		
		ImGui::Separator();

		ImGui::Checkbox("Heuristique value text", &m_bDrawDebugTexts);
	}
	ImGui::PopID();
}
*/

float AStar::ComputeHeuristic(const pair<int, int>& start, const pair<int, int>& end, EHeuristic eHeuristic, float fWeight)
{
	switch (eHeuristic)
	{
		case EHeuristic::Manhattan: { return Utility::GetManhattanDistance(start, end) * fWeight; };
		case EHeuristic::Euclidean: { return Utility::GetEuclideanDistance(start, end) * fWeight; };
		case EHeuristic::Chebyshev: {return Utility::GetChebyshevDistance(start, end) * fWeight; };
		case EHeuristic::Null: { return 0; };
	}

	return 0;
}
