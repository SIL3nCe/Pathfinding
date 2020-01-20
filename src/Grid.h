#pragma once

#include "Cell.h"

#define GRID_SIZE 30
#define CELL_SIZE 20.0f
#define CELL_OUTLINE_SIZE 2

class Grid
{
public:
	void Initialize(void);

	void Draw(sf::RenderWindow & window);
	
	void Clear(void);
	void Reset(void);

	void SetCaseColor(const std::pair<int, int>& vCase, const sf::Color& color);

	void OnMouseClicked(int posX, int posY);
	void OnMouseMoved(int posX, int posY);
	void OnMouseReleased(void);

	bool GetScreenCoordFromCell(int x, int y, sf::Vector2f& vLocation) const;
	bool GetScreenCoordFromCell(const std::pair<int, int>& vNode, sf::Vector2f& vLocation) const;

	bool IsValidID(const std::pair<int, int>& vNode) const;
	inline bool IsValidID(int x, int y) const;

	bool IsWalkable(const std::pair<int, int>& vNode) const;
	inline bool IsWalkable(int x, int y) const;

	const std::pair<int, int>& GetStart(void) const { return m_vStart; }
	const std::pair<int, int>& GetEnd(void) const { return m_vEnd; }

private:
	Cell m_aaGrid[GRID_SIZE][GRID_SIZE];
	std::pair<int, int> m_vStart;
	std::pair<int, int> m_vEnd;

	ECellState m_eStateToApply;
};
