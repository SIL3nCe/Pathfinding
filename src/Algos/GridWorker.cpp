#include "GridWorker.h"
#include "Utility.h"

using namespace std;

GridWorker::GridWorker(int width, int height, const pair<int, int>& vStart, const pair<int, int>& vEnd)
{
	m_width = width;
	m_height = height;

	m_vStart = vStart;
	m_vEnd = vEnd;

	for (int i = 0; i < m_height; ++i)
	{
		vector<bool> aLine(width);
		m_aaGrid.push_back(aLine);
	}
}

vector<vector<bool>>& GridWorker::GetGridToFill()
{
	return m_aaGrid;
}

void GridWorker::ComputeNeighboursOfCurrent(const pair<int, int>& vCurrentNode, bool bUseDiagonal, vector<pair<int, int>>& aNeighbours) const
{
	aNeighbours.clear();

	pair<int, int> vTestNode = vCurrentNode + Utility::CellTop;

	// Top
	bool bTopWalkable = IsWalkable(vTestNode);
	if (bTopWalkable)
	{
		aNeighbours.push_back(vTestNode);
	}

	// Right
	vTestNode = vCurrentNode + Utility::CellRight;
	bool bRightWalkable = IsWalkable(vTestNode);
	if (bRightWalkable)
	{
		aNeighbours.push_back(vTestNode);
	}

	// Bottom
	vTestNode = vCurrentNode + Utility::CellBottom;
	bool bBottomWalkable = IsWalkable(vTestNode);
	if (bBottomWalkable)
	{
		aNeighbours.push_back(vTestNode);
	}

	// Left
	vTestNode = vCurrentNode + Utility::CellLeft;
	bool bLeftWalkable = IsWalkable(vTestNode);
	if (bLeftWalkable)
	{
		aNeighbours.push_back(vTestNode);
	}

	if (bUseDiagonal)
	{
		// Top Left
		vTestNode = vCurrentNode + Utility::CellTopLeft;
		if (IsWalkable(vTestNode) && (bTopWalkable || bLeftWalkable))
		{
			aNeighbours.push_back(vTestNode);
		}

		// Top Right
		vTestNode = vCurrentNode + Utility::CellTopRight;
		if (IsWalkable(vTestNode) && (bTopWalkable || bRightWalkable))
		{
			aNeighbours.push_back(vTestNode);
		}

		// Bottom Right
		vTestNode = vCurrentNode + Utility::CellBottomRight;
		if (IsWalkable(vTestNode) && (bBottomWalkable || bRightWalkable))
		{
			aNeighbours.push_back(vTestNode);
		}

		// Bottom Left
		vTestNode = vCurrentNode + Utility::CellBottomLeft;
		if (IsWalkable(vTestNode) && (bBottomWalkable || bLeftWalkable))
		{
			aNeighbours.push_back(vTestNode);
		}
	}
}

bool GridWorker::IsValidID(const pair<int, int>& vNode) const
{
	return IsValidID(vNode.first, vNode.second);
}

inline bool GridWorker::IsValidID(int x, int y) const
{
	return (x >= 0 && x < m_height && y >= 0 && y < m_width);
}

bool GridWorker::IsWalkable(const pair<int, int>& vNode) const
{
	return IsWalkable(vNode.first, vNode.second);
}

inline bool GridWorker::IsWalkable(int x, int y) const
{
	return IsValidID(x, y) && m_aaGrid[x][y];
}
