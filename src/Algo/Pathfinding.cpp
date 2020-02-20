#include "Pathfinding.h"

void Pathfinding::Initialize(Grid& grid, sf::Font& font)
{
	m_pGrid = &grid;
	m_pFont = &font;

    m_fLength = 0.0f;
    m_fTime = 0.0f;
    m_fAsyncTime = 0.0f;
    m_steps = 0;

    m_bGuiOpen = true;
}

void Pathfinding::Start(void)
{
    m_fLength = 0.0f;
    m_fTime = 0.0f;
    m_fAsyncTime = 0.0f;
    m_steps = 0;

    m_asynClock.restart();
}

void Pathfinding::Stop(void)
{
    m_fAsyncTime = m_asynClock.getElapsedTime().asSeconds();
}

void Pathfinding::DrawGuiStatistics(void)
{
    if (ImGui::Begin("Stats"))
    {
        {
            char buf[32];
            sprintf(buf, "%.3f", m_fLength);
            ImGui::LabelText(buf, "Length: ");
        }
        {
            char buf[32];
            sprintf(buf, "%.3f", m_fTime);
            ImGui::LabelText(buf, "Time: ");
        }
        {
            char buf[32];
            sprintf(buf, "%.3f", m_fAsyncTime);
            ImGui::LabelText(buf, "Time (Async): ");
        }
        {
            char buf[32];
            sprintf(buf, "%d", m_steps);
            ImGui::LabelText(buf, "Steps: ");
        }

        ImGui::End();
    }
}
