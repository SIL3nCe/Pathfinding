#pragma once

#include <SFML/Graphics.hpp>

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

	void SetState(ECellState eState, bool bForce = false);
	ECellState GetState(void) const;

	void SetColor(const sf::Color& color);

private:
	sf::RectangleShape m_shape;

	ECellState m_eState;
};
