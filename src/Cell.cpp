#include "Cell.h"

void Cell::Initialize(float fSize, float fOutlineThickness, const sf::Vector2f& vLocation)
{
	m_shape.setSize(sf::Vector2f(fSize, fSize));
	m_shape.setPosition(vLocation);
	m_shape.setFillColor(sf::Color::White);

	m_shape.setOutlineThickness(fOutlineThickness);
	m_shape.setOutlineColor(sf::Color::Black);

	m_eState = ECellState::Empty;
}

void Cell::Draw(sf::RenderWindow & window)
{
	window.draw(m_shape);
}

void Cell::SetState(ECellState eState, bool bForce /*= false*/)
{
	switch (eState)
	{
		case ECellState::Empty:
		{
			if (!bForce && (m_eState == ECellState::Start || m_eState == ECellState::End))
				return;

			m_shape.setFillColor(sf::Color::White);
		}
		break;
		case ECellState::Wall:
		{
			if (!bForce && (m_eState == ECellState::Start || m_eState == ECellState::End))
				return;

			m_shape.setFillColor(sf::Color::Black);
		}
		break;
		case ECellState::Start:
		{
			m_shape.setFillColor(sf::Color::Green);
		}
		break;
		case ECellState::End:
		{
			m_shape.setFillColor(sf::Color::Red);
		}
		break;
	}

	m_eState = eState;
}

ECellState Cell::GetState(void) const
{
	return m_eState;
}

void Cell::SetColor(const sf::Color& color)
{
	m_shape.setFillColor(color);
}
