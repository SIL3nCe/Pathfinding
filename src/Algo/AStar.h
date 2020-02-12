#pragma once

#include "Pathfinding.h"
#include <queue>

class AStar : public Pathfinding
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
	void ComputeMinHeuristiqueNodeInQueue(void);
	void ComputeNeighboursOfCurrent(void);

private:
	struct SDatas
	{
		bool bClosed;
		int heuristique;
		int cost;
		std::pair<int, int> vPrevious;
	};

	SDatas m_aaWorker[GRID_SIZE][GRID_SIZE];

	std::vector<std::pair<int, int>> m_aNodeQueue;
	std::vector<std::pair<int, int>> m_aNeighbours;

	std::pair<int, int> m_vCurrentNode;

	//Debug info
	std::vector<sf::Vertex> m_aPath;
	sf::Text m_aTexts[GRID_SIZE * GRID_SIZE];
	bool m_bDrawDebugTexts = false;
};
