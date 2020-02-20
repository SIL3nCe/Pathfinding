#pragma once

#include "Pathfinding.h"
#include <queue>

class BreadthFirst : public Pathfinding
{
public:
	virtual void Initialize(Grid& grid, sf::Font& font) override;

	virtual void Start(void) override;
	virtual bool Execute(void) override;
	virtual void Stop(void) override;

	virtual void DrawGui(void) override;

	virtual void Draw(sf::RenderWindow& window) override;
	virtual void Clear(void) override;

private:
	void ComputeNeighboursOfCurrent(void);

private:
	struct SDatas
	{
		bool bDiscovered;
		std::pair<int, int> vParent;
	};

	SDatas m_aaWorker[GRID_SIZE][GRID_SIZE];

	std::queue<std::pair<int, int>> m_aNodeQueue;
	std::vector<std::pair<int, int>> m_aNeighbours;

	std::pair<int, int> m_vCurrentNode;

	//Options
	bool m_bUseDiagonal;
	bool m_bBidirectional;

	//Debug info
	std::vector<sf::Vertex> m_aPath;
};
