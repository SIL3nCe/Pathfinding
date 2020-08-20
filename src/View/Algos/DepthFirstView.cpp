#include "DepthFirstView.h"

DepthFirstView::DepthFirstView()
: m_bUseDiagonal(true)
{
}

bool DepthFirstView::Execute(const GridWorker& Grid, std::vector<std::pair<int, int>>& aFinalPath, OnDoingOperationFctPtr OnDoingOperation /*= DefaultOnDoingOperation*/)
{
    m_algoClock.restart();
    bool bRes = DepthFirst::Execute(Grid, m_bUseDiagonal, aFinalPath, OnDoingOperation);

    m_fTime = m_algoClock.getElapsedTime().asSeconds();
    m_fTime *= 1000.0f;

    return bRes;
}

void DepthFirstView::DrawGuiAlgorithm(EAlgorithms& eSelectedAlgo)
{
    if (EAlgorithms::DepthFirst == eSelectedAlgo)
    {
        ImGui::SetNextTreeNodeOpen(true);
        if (ImGui::CollapsingHeader("Depth First"))
        {
            ImGui::Checkbox("Use Diagonal", &m_bUseDiagonal);
        }
    }
    else
    {
        ImGui::SetNextTreeNodeOpen(false);
        if (ImGui::CollapsingHeader("Depth First", ImGuiTreeNodeFlags_Bullet))
        {
            eSelectedAlgo = EAlgorithms::DepthFirst;
        }
    }
}

void DepthFirstView::DrawGuiStatistics()
{
    ImGui::Text("Depth First");
    AlgoView::DrawGuiStatistics();
}
