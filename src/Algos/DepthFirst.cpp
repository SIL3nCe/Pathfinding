#include "DepthFirst.h"
#include <vector>

using namespace std;

// https://en.wikipedia.org/wiki/Depth-first_search

bool DepthFirst::Execute(const GridWorker& Grid, bool bUseDiagonal, vector<pair<int, int>>& aFinalPath, OnDoingOperationFctPtr OnDoingOperation /*= DefaultOnDoingOperation*/)
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

	// Init queue
	vector<pair<int, int>> aQueue;

	// Setup start node
	const pair<int, int>& vStart = Grid.GetStart();
	aQueue.push_back(vStart);
	aaWorker[vStart.first][vStart.second].bProcessed = true;

	vector<pair<int, int>> aNeighbours;
	pair<int, int> vCurrentNode;

	while (!aQueue.empty())
	{
		vCurrentNode = aQueue.back();
		aQueue.pop_back();

		// Current is end of path
		if (vCurrentNode == Grid.GetEnd())
		{
			aFinalPath.clear();
			while (vCurrentNode.first != -1)
			{
				aFinalPath.push_back(vCurrentNode);
				vCurrentNode = aaWorker[vCurrentNode.first][vCurrentNode.second].vParent;
			}

			return true;
		}

		aaWorker[vCurrentNode.first][vCurrentNode.second].bProcessed = true;

		// Get its neihbours
		Grid.ComputeNeighboursOfCurrent(vCurrentNode, bUseDiagonal, aNeighbours);

		// Push neighbours
		int nNeighbours = aNeighbours.size();
		for (int i = 0; i < nNeighbours; ++i)
		{
			const pair<int, int>& vNode = aNeighbours[i];

			if (!aaWorker[vNode.first][vNode.second].bProcessed)
			{
				aaWorker[vNode.first][vNode.second].vParent = vCurrentNode;

				aQueue.push_back(vNode);

				OnDoingOperation(EOperations::QueuedNode, vNode);
			}
		}

		OnDoingOperation(EOperations::ClosedNode, vCurrentNode);
	}

	return false;
}
