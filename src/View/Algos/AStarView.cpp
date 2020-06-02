#include "AStarView.h"

AStarView::AStarView()
: m_bUseDiagonal(true)
, m_eHeuristic(EHeuristic::Manhattan)
, m_fWeight(1.0f)
{
}

bool AStarView::Execute(const GridWorker& Grid, std::vector<std::pair<int, int>>& aFinalPath, OnDoingOperationFctPtr OnDoingOperation /* = DefaultOnDoingOperation*/)
{
    m_algoClock.restart();
    bool bRes = AStar::Execute(Grid, m_bUseDiagonal, m_eHeuristic, m_fWeight, aFinalPath, OnDoingOperation);
   
    m_fTime = m_algoClock.getElapsedTime().asSeconds();
    m_fTime *= 1000.0f;

    return bRes;
}

void AStarView::DrawGuiAlgorithm(EAlgorithms& eSelectedAlgo)
{
    if (EAlgorithms::AStar == eSelectedAlgo)
    {
        ImGui::SetNextTreeNodeOpen(true);
        if (ImGui::CollapsingHeader("A*"))
        {
            if (ImGui::RadioButton("Manhattan", m_eHeuristic == EHeuristic::Manhattan))
                m_eHeuristic = EHeuristic::Manhattan;
            if (ImGui::RadioButton("Euclidean", m_eHeuristic == EHeuristic::Euclidean))
                m_eHeuristic = EHeuristic::Euclidean;
            if (ImGui::RadioButton("Chebyshev", m_eHeuristic == EHeuristic::Chebyshev))
                m_eHeuristic = EHeuristic::Chebyshev;

            ImGui::Checkbox("Use Diagonal", &m_bUseDiagonal);
            ImGui::InputFloat("Weight", &m_fWeight);
        }
    }
    else
    {
        ImGui::SetNextTreeNodeOpen(false);
        if (ImGui::CollapsingHeader("A*", ImGuiTreeNodeFlags_Bullet))
        {
            eSelectedAlgo = EAlgorithms::AStar;
        }
    }
}

void AStarView::DrawGuiStatistics()
{
    ImGui::Text("A*");
    AlgoView::DrawGuiStatistics();
}
