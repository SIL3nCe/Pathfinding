#include "Dijkstra.h"
#include <queue>

using namespace std;

// https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm

bool Dijkstra::Execute(const GridWorker& Grid, bool bUseDiagonal, vector<pair<int, int>>& aFinalPath, OnDoingOperationFctPtr OnDoingOperation /*= DefaultOnDoingOperation*/)
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

	// Init priority queue
	auto compare = [&](pair<int, int>& left, pair<int, int>& right)
	{
		return aaWorker[left.first][left.second].fDistance > aaWorker[right.first][right.second].fDistance;
	};

	priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> aPrioQueue(compare);

	// Setup start node	
	const pair<int, int>& vStart = Grid.GetStart();
	aaWorker[vStart.first][vStart.second].fDistance = 0.0f;
	aPrioQueue.push(vStart);

	pair<int, int> vCurrentNode;

	while (aPrioQueue.size() != 0)
	{
		vCurrentNode = aPrioQueue.top();
		aPrioQueue.pop();

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

		// Get its neihbours
		Grid.ComputeNeighboursOfCurrent(vCurrentNode, bUseDiagonal, m_aNeighbours);

		// Compute distance to those neighbours
		int nNeighbours = m_aNeighbours.size();
		for (int i = 0; i < nNeighbours; ++i)
		{
			const pair<int, int>& vNode = m_aNeighbours[i];

			if (aaWorker[vNode.first][vNode.second].bQueued)
				continue;

			// Update dist
			float fAdd = (vNode.first == vCurrentNode.first || vNode.second == vCurrentNode.second) ? 1.0f : SquareRootOf2;
			float newDist = aaWorker[vCurrentNode.first][vCurrentNode.second].fDistance + fAdd;

			// Special case with diagonale, do not override cheapest dist
			if (bUseDiagonal && newDist > aaWorker[vNode.first][vNode.second].fDistance)
				continue;

			if (newDist < aaWorker[vNode.first][vNode.second].fDistance)
			{
				aaWorker[vNode.first][vNode.second].fDistance = newDist;
				aaWorker[vNode.first][vNode.second].vPrevious = vCurrentNode;
				aaWorker[vNode.first][vNode.second].bQueued = true;

				aPrioQueue.push(vNode);
				OnDoingOperation(EOperations::QueuedNode, vNode);
			}
		}

		OnDoingOperation(EOperations::ClosedNode, vCurrentNode);
	}

	return false;
}
