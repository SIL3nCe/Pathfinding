#pragma once

#include "Case.h"

#define GRID_SIZE 50
#define CASE_SIZE 20.0f
#define CASE_OUTLINE_SIZE 2

class Grid
{
public:
	void Initialize(void);

	void Draw(sf::RenderWindow & window);
	
	void Reset(void);

	void SetCaseColor(const std::pair<int, int>& vCase, const sf::Color& color);

	void OnMouseClicked(int posX, int posY);
	void OnMouseMoved(int posX, int posY);
	void OnMouseReleased(void);

	bool IsValidID(const std::pair<int, int>& vNode) const;
	inline bool IsValidID(int x, int y) const;

	inline bool IsWalkable(int x, int y) const;

	const std::pair<int, int>& GetStart(void) const { return m_vStart; }
	const std::pair<int, int>& GetEnd(void) const { return m_vEnd; }

private:
	Case m_aaGrid[GRID_SIZE][GRID_SIZE];
	std::pair<int, int> m_vStart;
	std::pair<int, int> m_vEnd;

	ECaseState m_eStateToApply;
};

