#include "Dijkstra.h"
#include <queue>

using namespace std;

// https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm

void Dijkstra::Execute(const GridWorker& Grid, bool bUseDiagonal, vector<pair<int, int>>& aFinalPath, void(*OnDoingOperation)(EOperations, const pair<int, int>&) /*= DefaultOnDoingOperation*/)
{
	vector<vector<SDatas>> aaWorker; //TODO Find a better way

	auto compare = [&](pair<int, int>& left, pair<int, int>& right)
	{
		return aaWorker[left.first][left.second].fDistance > aaWorker[right.first][right.second].fDistance;
	};

	priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> aPrioQueue(compare);

	for (int i = 0; i < Grid.GetHeight(); ++i)
	{
		vector<SDatas> aLine(Grid.GetWidth());
		for (int j = 0; j < Grid.GetWidth(); ++j)
		{
			aLine[j].bQueued = false;
			aLine[j].fDistance= static_cast<float>(UINT_MAX - 1);
			aLine[j].vPrevious = { -1, -1 };
		}
		aaWorker.push_back(aLine);
	}
	
	pair<int, int> vCurrentNode = Grid.GetStart();
	aaWorker[vCurrentNode.first][vCurrentNode.second].fDistance = 0.0f;

	aPrioQueue.push(vCurrentNode);

	while (aPrioQueue.size() != 0)
	{
		vCurrentNode = aPrioQueue.top();
		aPrioQueue.pop();

		// End check
		if (vCurrentNode == Grid.GetEnd())
			break;

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

	// Construct and return path
	aFinalPath.clear();

	aFinalPath.push_back(Grid.GetEnd());
	while (true)
	{
		vCurrentNode = aaWorker[vCurrentNode.first][vCurrentNode.second].vPrevious;
		if (vCurrentNode.first == -1)
			break;

		aFinalPath.push_back(vCurrentNode);
	}
}
