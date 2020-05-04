#pragma once

#include <SFML/Graphics.hpp>
#include "Utility.h"
#include <stack>

enum class ECellState
{
	Empty,
	Wall,
	Start,
	End
};

class Cell
{
public:
	void Initialize(float fSize, float fOutlineThickness, const sf::Vector2f & vLocation);

	void Draw(sf::RenderWindow & window);

	const sf::Vector2f GetScreenCoord() const;

	void SetState(ECellState eState, bool bForce = false);
	ECellState GetState() const;

	void ClearDebugInfo();

	void DoOperation(EOperations eOperation);
	void UndoOperation();

private:
	void ApplyOperation();

private:
	sf::RectangleShape m_shape;
	
	sf::Vector2f m_aScreenCoord;

	ECellState m_eState;

	std::stack<EOperations> m_aOperations;
};
