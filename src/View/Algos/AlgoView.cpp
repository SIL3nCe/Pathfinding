#include "AlgoView.h"

#include "imgui.h"
#include "imgui-SFML.h"

AlgoView::AlgoView()
: m_fTime(0.0f)
, m_steps(0)
, m_fLength(0.0f)
, m_algoClock()
{
}

bool AlgoView::Execute(const GridWorker& Grid, std::vector<std::pair<int, int>>& aFinalPath, OnDoingOperationFctPtr OnDoingOperation)
{
	return false;
}

void AlgoView::DrawGuiAlgorithm(EAlgorithms& eSelectedAlgo)
{
}

void AlgoView::DrawGuiStatistics()
{
    {
        char buf[32];
        sprintf(buf, "%.3f", m_fLength);
        ImGui::LabelText(buf, "Length: ");
    }
    {
        char buf[32];
        sprintf(buf, "%.3f", m_fTime);
        ImGui::LabelText(buf, "Time (ms): ");
    }
    {
        char buf[32];
        sprintf(buf, "%d", m_steps);
        ImGui::LabelText(buf, "Steps: ");
    }
}

void AlgoView::SetStatsStep(float fSteps)
{
	m_steps = fSteps;
}

void AlgoView::SetStatsLength(float fLength)
{
	m_fLength = fLength;
}

void AlgoView::ResetStats()
{
	m_fTime = 0.0f;
	m_steps = 0;
	m_fLength = 0.0f;
}
