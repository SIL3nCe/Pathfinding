#include "AStarBidirView.h"

AStarBidirView::AStarBidirView()
: m_algo()
, m_bUseDiagonal(true)
, m_eHeuristic(EHeuristic::Manhattan)
, m_fWeight(1.0f)
{
}

bool AStarBidirView::Execute(const GridWorker& Grid, std::vector<std::pair<int, int>>& aFinalPath, OnDoingOperationFctPtr OnDoingOperation /* = DefaultOnDoingOperation*/)
{
    m_algoClock.restart();
    bool bRes = m_algo.ExecuteBidirectional(Grid, m_bUseDiagonal, m_eHeuristic, m_fWeight, aFinalPath, OnDoingOperation);
   
    m_fTime = m_algoClock.getElapsedTime().asSeconds();
    m_fTime *= 1000.0f;

    return bRes;
}

void AStarBidirView::DrawGuiAlgorithm(EAlgorithms& eSelectedAlgo)
{
    if (EAlgorithms::AStarBidir == eSelectedAlgo)
    {
        ImGui::SetNextTreeNodeOpen(true);
        if (ImGui::CollapsingHeader("A* Bidir"))
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
        if (ImGui::CollapsingHeader("A* Bidir", ImGuiTreeNodeFlags_Bullet))
        {
            eSelectedAlgo = EAlgorithms::AStarBidir;
        }
    }
}

void AStarBidirView::DrawGuiStatistics()
{
    ImGui::Text("A* BiDir");
    AlgoView::DrawGuiStatistics();
}
