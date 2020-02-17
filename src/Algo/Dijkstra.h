#pragma once

#include "Pathfinding.h"

class Dijkstra : public Pathfinding
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
	void ComputeMinDistNodeInQueue(void);
	void ComputeNeighboursOfCurrent(void);

private:
	struct SDatas
	{
		int distance;
		std::pair<int, int> vPrevious;
	};

	SDatas m_aaWorker[GRID_SIZE][GRID_SIZE];

	std::vector<std::pair<int, int>> m_aNodeQueue;
	std::vector<std::pair<int, int>> m_aNeighbours;

	std::pair<int, int> m_vCurrentNode;

	//Options
	bool m_bUseDiagonal;
	bool m_bBidirectional;

	bool m_bDrawDebugTexts;

	//Debug info
	std::vector<sf::Vertex> m_aPath;
	sf::Text m_aTexts[GRID_SIZE * GRID_SIZE];
};
