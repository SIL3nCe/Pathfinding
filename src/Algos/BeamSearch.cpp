#include "BeamSearch.h"
#include <set>

using namespace std;

// https://en.wikipedia.org/wiki/Beam_search

bool BeamSearch::Execute(const GridWorker& Grid, bool bUseDiagonal, EHeuristic eHeuristic, float fWeight, int beamWidth, vector<pair<int, int>>& aFinalPath, OnDoingOperationFctPtr OnDoingOperation /*= DefaultOnDoingOperation*/)
{
	// Init worker
	vector<vector<SDatas>> aaWorker;

	int gridHeight = Grid.GetHeight();
	int gridWidth = Grid.GetWidth();
	for (int i = 0; i < gridHeight; ++i)
	{
		vector<SDatas> aLine(gridWidth);
		aaWorker.push_back(aLine);
	}

	// Init multiset
	auto compare = [&aaWorker](const pair<int, int>& left, const pair<int, int>& right)
	{
		return aaWorker[left.first][left.second].fScore < aaWorker[right.first][right.second].fScore;
	};

	multiset<pair<int, int>, decltype(compare)> aPrioSet(compare);

	// Setup start node
	const pair<int, int>& vStart = Grid.GetStart();
	aaWorker[vStart.first][vStart.second].bQueued = true;
	aaWorker[vStart.first][vStart.second].fCost = 0.0f;
	aaWorker[vStart.first][vStart.second].fHeuristic = ComputeHeuristic(vStart, Grid.GetEnd(), eHeuristic, fWeight);

	aPrioSet.insert(vStart);
	OnDoingOperation(EOperations::QueuedNode, vStart);

	pair<int, int> vCurrentNode;

	while (aPrioSet.size() != 0)
	{
		vCurrentNode = *aPrioSet.begin();
		aPrioSet.erase(aPrioSet.begin());

		aaWorker[vCurrentNode.first][vCurrentNode.second].bClosed = true;
		OnDoingOperation(EOperations::ClosedNode, vCurrentNode);

		// End check
		if (vCurrentNode == Grid.GetEnd())
		{
			aFinalPath.clear();
			while (vCurrentNode.first != -1)
			{
				aFinalPath.push_back(vCurrentNode);
				vCurrentNode = aaWorker[vCurrentNode.first][vCurrentNode.second].vPrevious;
			}

			return true;
		}

		// Get neighbours
		Grid.ComputeNeighboursOfCurrent(vCurrentNode, bUseDiagonal, m_aNeighbours);

		// Compute distance to those neighbours
		int nNeighbours = m_aNeighbours.size();
		for (int i = 0; i < nNeighbours; ++i)
		{
			const pair<int, int>& vNode = m_aNeighbours[i];

			SDatas* pData = &aaWorker[vNode.first][vNode.second];

			if (pData->bClosed)
				continue;

			float fAdd = (vNode.first == vCurrentNode.first || vNode.second == vCurrentNode.second) ? 1.0f : SquareRootOf2;
			float newCost = aaWorker[vCurrentNode.first][vCurrentNode.second].fCost + fAdd;

			if (!pData->bQueued || newCost < pData->fCost)
			{
				pData->vPrevious = vCurrentNode;
				pData->fCost = newCost;
				if (!pData->bQueued)
				{
					pData->fHeuristic = ComputeHeuristic(vNode, Grid.GetEnd(), eHeuristic, fWeight); // Compute it only the first
					pData->bQueued = true;
					OnDoingOperation(EOperations::QueuedNode, vNode);
				}
				pData->fScore = pData->fCost + pData->fHeuristic;

				aPrioSet.insert(vNode); // Will update the key if already exists
			}
		}

		while (aPrioSet.size() > beamWidth)
		{
			aPrioSet.erase(std::prev(aPrioSet.end()));
		}
	}

	return false;
}

float BeamSearch::ComputeHeuristic(const pair<int, int>& start, const pair<int, int>& end, EHeuristic eHeuristic, float fWeight)
{
	switch (eHeuristic)
	{
		case EHeuristic::Manhattan: return Utility::GetManhattanDistance(start, end) * fWeight;
		case EHeuristic::Euclidean: return Utility::GetEuclideanDistance(start, end) * fWeight;
		case EHeuristic::Chebyshev: return Utility::GetChebyshevDistance(start, end) * fWeight;
		case EHeuristic::Null: return 0.0f;
	}

	return 0.0f;
}