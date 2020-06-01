#include "BreadthFirstView.h"

BreadthFirstView::BreadthFirstView()
: m_algo()
, m_bUseDiagonal(true)
{
}

bool BreadthFirstView::Execute(const GridWorker& Grid, std::vector<std::pair<int, int>>& aFinalPath, OnDoingOperationFctPtr OnDoingOperation /* = DefaultOnDoingOperation*/)
{
    m_algoClock.restart();
    bool bRes = m_algo.Execute(Grid, m_bUseDiagonal, aFinalPath, OnDoingOperation);

    m_fTime = m_algoClock.getElapsedTime().asSeconds();
    m_fTime *= 1000.0f;

    return bRes;
}

void BreadthFirstView::DrawGuiAlgorithm(EAlgorithms& eSelectedAlgo)
{
    if (EAlgorithms::BreadthFirst == eSelectedAlgo)
    {
        ImGui::SetNextTreeNodeOpen(true);
        if (ImGui::CollapsingHeader("Breadth First"))
        {
            ImGui::Checkbox("Use Diagonal", &m_bUseDiagonal);
        }
    }
    else
    {
        ImGui::SetNextTreeNodeOpen(false);
        if (ImGui::CollapsingHeader("Breadth First", ImGuiTreeNodeFlags_Bullet))
        {
            eSelectedAlgo = EAlgorithms::BreadthFirst;
        }
    }
}

void BreadthFirstView::DrawGuiStatistics()
{
    ImGui::Text("Breadth First");
    AlgoView::DrawGuiStatistics();
}
