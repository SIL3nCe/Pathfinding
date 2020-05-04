#include "AStarView.h"

#include "imgui.h"
#include "imgui-SFML.h"

AStarView::AStarView()
: m_algo()
, m_bAStarUseDiagonal(true)
, m_eAStartHeuristic(EHeuristic::Manhattan)
, m_fAStarWeight(1.0f)
{
}

bool AStarView::Execute(const GridWorker& Grid, std::vector<std::pair<int, int>>& aFinalPath, OnDoingOperationFctPtr OnDoingOperation /* = DefaultOnDoingOperation*/)
{
    m_algoClock.restart();
    bool bRes = m_algo.Execute(Grid, m_bAStarUseDiagonal, m_eAStartHeuristic, m_fAStarWeight, aFinalPath, OnDoingOperation);
   
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
            if (ImGui::RadioButton("Manhattan", m_eAStartHeuristic == EHeuristic::Manhattan))
                m_eAStartHeuristic = EHeuristic::Manhattan;
            if (ImGui::RadioButton("Euclidean", m_eAStartHeuristic == EHeuristic::Euclidean))
                m_eAStartHeuristic = EHeuristic::Euclidean;
            if (ImGui::RadioButton("Chebyshev", m_eAStartHeuristic == EHeuristic::Chebyshev))
                m_eAStartHeuristic = EHeuristic::Chebyshev;

            ImGui::Checkbox("Use Diagonal", &m_bAStarUseDiagonal);
            ImGui::InputFloat("Weight", &m_fAStarWeight);
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
