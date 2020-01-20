#include "Pathfinding.h"

void Pathfinding::Initialize(Grid& grid)
{
	m_pGrid = &grid;

	if (!m_font.loadFromFile("Resources\\Gold-Regular.ttf"))
	{
		printf("Pathfinding::Initialize Cannot load font");
	}
}

void Pathfinding::Draw(sf::RenderWindow& window)
{
}

void Pathfinding::Clear(void)
{
}
