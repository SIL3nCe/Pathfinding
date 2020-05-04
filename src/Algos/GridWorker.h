#pragma once

#include <vector>

class GridWorker
{
public:
	GridWorker() = delete;
	GridWorker(const GridWorker & grid) = delete;
	GridWorker(GridWorker&& grid) = delete;
	GridWorker(int width, int height, const std::pair<int, int> & vStart, const std::pair<int, int> & vEnd);

	std::vector<std::vector<bool>>& GetGridToFill();

	void ComputeNeighboursOfCurrent(const std::pair<int, int>& vCurrentNode, bool bUseDiagonal, std::vector<std::pair<int, int>>& aNeighbours) const;

	bool IsValidID(const std::pair<int, int>& vNode) const;
	inline bool IsValidID(int x, int y) const;

	bool IsWalkable(const std::pair<int, int>& vNode) const;
	inline bool IsWalkable(int x, int y) const;

	const int GetWidth() const { return m_width; }
	const int GetHeight() const { return m_height; }

	const std::pair<int, int>& GetStart() const { return m_vStart; }
	const std::pair<int, int>& GetEnd() const { return m_vEnd; }

private:

	std::vector<std::vector<bool>>m_aaGrid;

	int m_width;
	int m_height;

	std::pair<int, int> m_vStart;
	std::pair<int, int> m_vEnd;
};
