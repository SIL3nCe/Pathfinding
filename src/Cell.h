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

	const sf::Vector2f GetScreenCoord(void) const;

	void SetState(ECellState eState, bool bForce = false);
	ECellState GetState(void) const;

	void SetColor(const sf::Color& color);

private:
	sf::RectangleShape m_shape;
	
	sf::Vector2f m_aScreenCoord;

	ECellState m_eState;
};
