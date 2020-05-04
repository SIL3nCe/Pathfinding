#include "DijkstraView.h"

#include "imgui.h"
#include "imgui-SFML.h"

DijkstraView::DijkstraView()
: m_algo()
, m_bDijkstraUseDiagonal(true)
{
}

bool DijkstraView::Execute(const GridWorker& Grid, std::vector<std::pair<int, int>>& aFinalPath, OnDoingOperationFctPtr OnDoingOperation /* = DefaultOnDoingOperation*/)
{
    m_algoClock.restart();
    bool bRes = m_algo.Execute(Grid, m_bDijkstraUseDiagonal, aFinalPath, OnDoingOperation);

    m_fTime = m_algoClock.getElapsedTime().asSeconds();
    m_fTime *= 1000.0f;

    return bRes;
}

void DijkstraView::DrawGuiAlgorithm(EAlgorithms& eSelectedAlgo)
{
    if (EAlgorithms::Dijksta == eSelectedAlgo)
    {
        ImGui::SetNextTreeNodeOpen(true);
        if (ImGui::CollapsingHeader("Dijkstra"))
        {
            ImGui::Checkbox("Use Diagonal", &m_bDijkstraUseDiagonal);
        }
    }
    else
    {
        ImGui::SetNextTreeNodeOpen(false);
        if (ImGui::CollapsingHeader("Dijkstra", ImGuiTreeNodeFlags_Bullet))
        {
            eSelectedAlgo = EAlgorithms::Dijksta;
        }
    }
}

void DijkstraView::DrawGuiStatistics()
{
    ImGui::Text("Dijkstra");
    AlgoView::DrawGuiStatistics();
}
