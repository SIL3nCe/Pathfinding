#include "BreadthFirst.h"

using namespace std;

// https://en.wikipedia.org/wiki/Breadth-first_search

bool BreadthFirst::Execute(const GridWorker& Grid, bool bUseDiagonal, vector<pair<int, int>>& aFinalPath, void(*OnDoingOperation)(EOperations, const pair<int, int>&) /*= DefaultOnDoingOperation*/)
{
	vector<vector<SDatas>> aaWorker;

	queue<pair<int, int>> aQueue;

	for (int i = 0; i < Grid.GetHeight(); ++i)
	{
		vector<SDatas> aLine(Grid.GetWidth());
		for (int j = 0; j < Grid.GetWidth(); ++j)
		{
			aLine[j].bDiscovered = false;
			aLine[j].vParent = { -1, -1 };
		}
		aaWorker.push_back(aLine);
	}

	const pair<int, int>& vStart = Grid.GetStart();
	aQueue.push(vStart);
	aaWorker[vStart.first][vStart.second].bDiscovered = true;

	pair<int, int> vCurrentNode;

	while (!aQueue.empty())
	{
		vCurrentNode = aQueue.front();
		aQueue.pop();

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

		// Get its neihbours
		Grid.ComputeNeighboursOfCurrent(vCurrentNode, bUseDiagonal, m_aNeighbours);

		// Compute distance to those neighbours
		int nNeighbours = m_aNeighbours.size();
		for (int i = 0; i < nNeighbours; ++i)
		{
			const pair<int, int>& vNode = m_aNeighbours[i];

			if (!aaWorker[vNode.first][vNode.second].bDiscovered)
			{
				aaWorker[vNode.first][vNode.second].bDiscovered = true;
				aaWorker[vNode.first][vNode.second].vParent = vCurrentNode;

				aQueue.push(vNode);

				OnDoingOperation(EOperations::QueuedNode, vNode);
			}
		}

		OnDoingOperation(EOperations::ClosedNode, vCurrentNode);
	}

	return false;
}
