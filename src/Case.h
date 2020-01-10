#pragma once

#include <SFML/Graphics.hpp>

enum class ECaseState
{
	Empty,
	Wall,
	Start,
	End
};

class Case
{
public:
	void Initialize(float fSize, float fOutlineThickness, const sf::Vector2f & vLocation);

	void Draw(sf::RenderWindow & window);

	void SetState(ECaseState eState, bool bForce = false);
	ECaseState GetState(void);

	void SetColor(const sf::Color& color);

private:
	sf::RectangleShape m_shape;

	ECaseState m_eState;
};
