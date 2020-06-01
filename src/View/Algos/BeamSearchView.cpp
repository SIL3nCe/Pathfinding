#include "BeamSearchView.h"

BeamSearchView::BeamSearchView()
: m_algo()
, m_bUseDiagonal(true)
, m_eHeuristic(EHeuristic::Manhattan)
, m_fWeight(1.0f)
, m_beamWidth(20)
{
}

bool BeamSearchView::Execute(const GridWorker& Grid, std::vector<std::pair<int, int>>& aFinalPath, OnDoingOperationFctPtr OnDoingOperation /* = DefaultOnDoingOperation*/)
{
    m_algoClock.restart();
    bool bRes = m_algo.Execute(Grid, m_bUseDiagonal, m_eHeuristic, m_fWeight, m_beamWidth, aFinalPath, OnDoingOperation);

    m_fTime = m_algoClock.getElapsedTime().asSeconds();
    m_fTime *= 1000.0f;

    return bRes;
}

void BeamSearchView::DrawGuiAlgorithm(EAlgorithms& eSelectedAlgo)
{
    if (EAlgorithms::BeamSearch == eSelectedAlgo)
    {
        ImGui::SetNextTreeNodeOpen(true);
        if (ImGui::CollapsingHeader("Beam Search"))
        {
            if (ImGui::RadioButton("Manhattan", m_eHeuristic == EHeuristic::Manhattan))
                m_eHeuristic = EHeuristic::Manhattan;
            if (ImGui::RadioButton("Euclidean", m_eHeuristic == EHeuristic::Euclidean))
                m_eHeuristic = EHeuristic::Euclidean;
            if (ImGui::RadioButton("Chebyshev", m_eHeuristic == EHeuristic::Chebyshev))
                m_eHeuristic = EHeuristic::Chebyshev;

            ImGui::Checkbox("Use Diagonal", &m_bUseDiagonal);
            ImGui::InputFloat("Weight", &m_fWeight);
            ImGui::InputInt("Beam Width", &m_beamWidth);
        }
    }
    else
    {
        ImGui::SetNextTreeNodeOpen(false);
        if (ImGui::CollapsingHeader("Beam Search", ImGuiTreeNodeFlags_Bullet))
        {
            eSelectedAlgo = EAlgorithms::BeamSearch;
        }
    }
}

void BeamSearchView::DrawGuiStatistics()
{
    ImGui::Text("Beam Search");
    AlgoView::DrawGuiStatistics();
}
