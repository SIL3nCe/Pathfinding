#pragma once

#include "Cell.h"
#include "Utility.h"

#define GRID_SIZE 30
#define CELL_SIZE 20.0f
#define CELL_OUTLINE_SIZE 2

class GridWorker;

class GridView
{
public:
	GridView();

	void Draw(sf::RenderWindow & window);
	
	void Clear();
	void ClearDebugInfo();
	void Reset();

	void FillGridWorker(GridWorker * pGrid);

	void SetCaseColor(const std::pair<int, int>& vCase, const sf::Color& color);

	float DrawPath(const std::vector<std::pair<int, int>>& aPath);
	void SetDrawPath(bool bDraw);

	void DrawOperation(const SOperation& operation);

	void OnMouseClicked(int posX, int posY);
	void OnMouseMoved(int posX, int posY);
	void OnMouseReleased();

	bool GetScreenCoordFromCell(int x, int y, sf::Vector2f& vLocation) const;
	bool GetScreenCoordFromCell(const std::pair<int, int>& vNode, sf::Vector2f& vLocation) const;

	inline bool IsValidID(int x, int y) const;

	const std::pair<int, int>& GetStart() const { return m_vStart; }
	const std::pair<int, int>& GetEnd() const { return m_vEnd; }

private:
	Cell m_aaGrid[GRID_SIZE][GRID_SIZE];
	std::pair<int, int> m_vStart;
	std::pair<int, int> m_vEnd;

	ECellState m_eStateToApply;

	bool m_bDrawPath;
	std::vector<sf::Vertex> m_aPath;
};
