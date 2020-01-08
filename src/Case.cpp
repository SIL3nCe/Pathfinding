#include "Case.h"

void Case::Initialize(float fSize, float fOutlineThickness, const sf::Vector2f& vLocation)
{
	m_shape.setSize(sf::Vector2f(fSize, fSize));
	m_shape.setPosition(vLocation);
	m_shape.setFillColor(sf::Color::White);

	m_shape.setOutlineThickness(fOutlineThickness);
	m_shape.setOutlineColor(sf::Color::Black);

	m_eState = ECaseState::Empty;
}

void Case::Draw(sf::RenderWindow & window)
{
	window.draw(m_shape);
}

void Case::SetState(ECaseState eState)
{
	switch (eState)
	{
		case ECaseState::Empty:
		{
			if (m_eState != ECaseState::Start && m_eState != ECaseState::End)
				m_shape.setFillColor(sf::Color::White);
		}
		break;
		case ECaseState::Wall:
		{
			if (m_eState != ECaseState::Start && m_eState != ECaseState::End)
				m_shape.setFillColor(sf::Color::Black);
		}
		break;
		case ECaseState::Start:
		{
			m_shape.setFillColor(sf::Color::Green);
		}
		break;
		case ECaseState::End:
		{
			m_shape.setFillColor(sf::Color::Red);
		}
		break;
	}

	m_eState = eState;
}

ECaseState Case::GetState(void)
{
	return m_eState;
}
