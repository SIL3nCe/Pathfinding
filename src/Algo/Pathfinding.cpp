#include "Pathfinding.h"

void Pathfinding::Initialize(Grid& grid, sf::Font& font)
{
	m_pGrid = &grid;
	m_pFont = &font;

    m_fLength = 0.0f;
    m_fTime = 0.0f;
    m_fTimeAsync = 0.0f;
    m_steps = 0;
}

void Pathfinding::DrawGuiStatistics(void)
{
    if (ImGui::Begin("Stats"))
    {
        {
            char buf[32];
            sprintf(buf, "%f", m_fLength);
            ImGui::LabelText(buf, "Length: ");
        }
        {
            char buf[32];
            sprintf(buf, "%f", m_fTime);
            ImGui::LabelText(buf, "Time: ");
        }
        {
            char buf[32];
            sprintf(buf, "%f", m_fTimeAsync);
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
