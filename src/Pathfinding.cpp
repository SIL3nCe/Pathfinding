#include "Pathfinding.h"

#include "imgui.h"
#include "imgui-SFML.h"

#include "AlgoView.h"
#include "AStarView.h"
#include "DijkstraView.h"
#include "BreadthFirstView.h"

using namespace std;

std::vector<SOperation> Pathfinding::m_aOperationStack;

Pathfinding::Pathfinding()
: m_eState(EPathfindingState::GridUse)
, m_grid()
, m_eSelectedAlgo(EAlgorithms::AStar)
, m_currentStep(0)
, m_bRewind(false)
, m_bPause(true)
, m_frameBeforeDrawing(1)
, m_operationsToDrawPerFrames(4)
, m_frameCounter(0)
{
    buttonPlay.loadFromFile("Resources\\play.png");
    buttonRewind.loadFromFile("Resources\\playrewind.png");
    buttonPause.loadFromFile("Resources\\pause.png");
    buttonNext.loadFromFile("Resources\\next.png");
    buttonPrevious.loadFromFile("Resources\\previous.png");

    // Init in order of EAlgorithms
    m_aAlgoViews.reserve(static_cast<int>(EAlgorithms::Max));

    AStarView* pAStar = new AStarView();
    m_aAlgoViews.push_back(pAStar);
    DijkstraView* pDijkstra = new DijkstraView();
    m_aAlgoViews.push_back(pDijkstra);
    BreadthFirstView* pBreadthFirst = new BreadthFirstView();
    m_aAlgoViews.push_back(pBreadthFirst);
}

void Pathfinding::Update(float dt)
{
    switch (m_eState)
    {
        case EPathfindingState::GridUse:
        {
            if (!m_bPause)
            {
                m_frameCounter++;

                if (m_frameCounter >= m_frameBeforeDrawing)
                {
                    m_frameCounter = 0;
                    for (int i = 0; i < m_operationsToDrawPerFrames; ++i)
                    {
                        bool bStop = m_bRewind ? UndrawAStep() : DrawAStep();
                        if (bStop)
                        {
                            m_grid.SetDrawPath(!m_bRewind);
                            m_bPause = true;
                            break;
                        }
                    }
                }
            }
        }
        break;

        case EPathfindingState::ExecAlgo:
        {
            GridWorker gridWorker(GRID_SIZE, GRID_SIZE, m_grid.GetStart(), m_grid.GetEnd());
            m_grid.FillGridWorker(&gridWorker);
            vector<pair<int, int>> aPath;

            AlgoView* pAlgo = m_aAlgoViews[static_cast<int>(m_eSelectedAlgo)];
            pAlgo->Execute(gridWorker, aPath, Pathfinding::OnDoingOperation);

            pAlgo->SetStatsLength(m_grid.DrawPath(aPath));
            pAlgo->SetStatsStep(m_aOperationStack.size());

            SetState(EPathfindingState::GridUse);
        }
        break;
        
        case EPathfindingState::ExecAllAlgo:
        {
            GridWorker gridWorker(GRID_SIZE, GRID_SIZE, m_grid.GetStart(), m_grid.GetEnd());
            m_grid.FillGridWorker(&gridWorker);
            vector<pair<int, int>> aPath;

            int i = 0;
            for (AlgoView* pAlgo : m_aAlgoViews)
            {
                //TODO give a OnDoingOperationFctPtr which will only count operations for stats
                pAlgo->Execute(gridWorker, aPath, i == static_cast<int>(m_eSelectedAlgo) ? Pathfinding::OnDoingOperation : DefaultOnDoingOperation);

                pAlgo->SetStatsLength(m_grid.DrawPath(aPath));
                pAlgo->SetStatsStep(m_aOperationStack.size());
                i++;
            }

            SetState(EPathfindingState::GridUse);
        }
        break;
    }

    DrawGUI();
}

void Pathfinding::Draw(sf::RenderWindow& window)
{
    m_grid.Draw(window);
}

// Return true if last step
bool Pathfinding::DrawAStep()
{
    if (m_currentStep >= m_aOperationStack.size())
        return true;

    m_grid.DoOperation(m_aOperationStack[m_currentStep]);
    m_currentStep++;

    return false;
}

bool Pathfinding::UndrawAStep()
{
    if (m_currentStep <= 0)
        return true;
    
    m_currentStep--;
    m_grid.UndoOperation(m_aOperationStack[m_currentStep]);

    return false;
}

void Pathfinding::SetState(EPathfindingState eNewState)
{
    // Leave state
    switch (m_eState)
    {
        case EPathfindingState::GridUse:
        {
            m_grid.ClearDebugInfo();
            m_aOperationStack.clear();
        }
        break;

        case EPathfindingState::ExecAlgo:
        case EPathfindingState::ExecAllAlgo:
        {
            m_currentStep = 0;
            m_bRewind = false;
            m_bPause = false;
        }
        break;
    }

    m_eState = eNewState;

    // Entering state
    switch (m_eState)
    {
        case EPathfindingState::GridUse:
        {
        }
        break;

        case EPathfindingState::ExecAlgo:
        case EPathfindingState::ExecAllAlgo:
        {
            for (AlgoView* pAlgo : m_aAlgoViews)
            {
                pAlgo->ResetStats();
            }
        }
        break;
    }
}

void Pathfinding::DrawGUI()
{
    //
    //Statistics
    if (ImGui::Begin("Stats"))
    {
        int nElements = static_cast<int>(EAlgorithms::Max);

        ImGui::SetNextWindowContentSize(ImVec2(ImGui::GetFontSize() * 13.0f * nElements, 0.0f));
        ImGui::BeginChild("##ScrollingRegion", ImVec2(0.0f, 0.0f), true, ImGuiWindowFlags_HorizontalScrollbar);
        ImGui::Columns(nElements);

        for (AlgoView* pAlgo : m_aAlgoViews)
        {
            pAlgo->DrawGuiStatistics();
            ImGui::NextColumn();
        }

        ImGui::EndChild();

    }
    ImGui::End();

    //
    // Algorithms
    if (ImGui::Begin("Algorithms"))
    {
        ImGui::PushItemWidth(100.0f);

        for (AlgoView* pAlgo : m_aAlgoViews)
        {
            pAlgo->DrawGuiAlgorithm(m_eSelectedAlgo);
        }
    }
    ImGui::End();

    //
    // Actions buttons
    if (ImGui::Begin("Actions"))
    {
        if (ImGui::Button("Execute", sf::Vector2f(60.0f, 30.0f)))
        {
            if (m_eState == EPathfindingState::GridUse)
            {
                SetState(EPathfindingState::ExecAlgo);
            }
        }
        ImGui::SameLine();        
        if (ImGui::Button("Execute All", sf::Vector2f(85.0f, 30.0f)))
        {
            if (m_eState == EPathfindingState::GridUse)
            {
                SetState(EPathfindingState::ExecAllAlgo);
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Clear", sf::Vector2f(60.0f, 30.0f)))
        {
            if (m_eState == EPathfindingState::GridUse)
            {
                m_grid.Clear();
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Reset", sf::Vector2f(60.0f, 30.0f)))
        {
            if (m_eState == EPathfindingState::GridUse)
            {
                m_grid.Reset();
                //TODO + reset every values, stats, options, etc
            }
        }
    }
    ImGui::End();

    //
    // Animation options
    if (ImGui::Begin("Debug draw"))
    {
        ImGui::PushItemWidth(100.0f);

        if (ImGui::ImageButton(buttonPrevious, sf::Vector2f(30.0f, 30.0f)))
        {
            m_bPause = true;
            m_bRewind = true;
            UndrawAStep();
        }
        ImGui::SameLine();

        if (m_bPause || !m_bRewind)
        {
            if (ImGui::ImageButton(buttonRewind, sf::Vector2f(30.0f, 30.0f)))
            {
                if (0 != m_aOperationStack.size())
                {
                    m_bPause = false;
                    m_bRewind = true;

                    if (0 == m_currentStep)
                    {
                        m_currentStep = 0;
                        for (int i = 0; m_currentStep < m_aOperationStack.size();)
                        {
                            DrawAStep();
                        }
                    }
                }
            }
        }
        else
        {
            if (ImGui::ImageButton(buttonPause, sf::Vector2f(30.0f, 30.0f)))
            {
                m_bPause = true;
            }
        }
        ImGui::SameLine();

        if (m_bPause || m_bRewind)
        {
            if (ImGui::ImageButton(buttonPlay, sf::Vector2f(30.0f, 30.0f)))
            {
                if (0 != m_aOperationStack.size())
                {
                    m_bPause = false;
                    m_bRewind = false;

                    if (m_currentStep >= m_aOperationStack.size())
                    {
                        m_grid.ClearDebugInfo();
                        m_currentStep = 0;
                    }
                }
            }
        }
        else
        {
            if (ImGui::ImageButton(buttonPause, sf::Vector2f(30.0f, 30.0f)))
            {
                m_bPause = true;
            }
        }
        ImGui::SameLine();

        if (ImGui::ImageButton(buttonNext, sf::Vector2f(30.0f, 30.0f)))
        {
            m_bPause = true;
            m_bRewind = false;
            DrawAStep();
        }

        {
            char buf[32];
            sprintf(buf, "Operation %d/%d : ", m_currentStep, m_aOperationStack.size());
            ImGui::Text(buf);
        }
        ImGui::SameLine();
        if (m_currentStep <= m_aOperationStack.size() && m_currentStep > 0)
        {
            char buf[64];
            const SOperation& operation = m_aOperationStack[m_currentStep - 1];
            sprintf(buf, "(%d,%d) - %s", operation.vCellCoord.first, operation.vCellCoord.second, operation.eOperation == EOperations::QueuedNode ? "Queued" : "Closed");
            ImGui::Text(buf);
        }
        else
        {
            ImGui::Text("-");
        }

        ImGui::SliderInt("Frames between operations", &m_frameBeforeDrawing, 1, 10);
        ImGui::SliderInt("Operations per draw", &m_operationsToDrawPerFrames, 1, 20);
    }
    ImGui::End();
}

void Pathfinding::OnKeyPressed(sf::Keyboard::Key eKey)
{
    if (sf::Keyboard::R == eKey)
    {
        if (m_eState == EPathfindingState::GridUse)
        {
            m_grid.Reset();
        }
    }
    else if (sf::Keyboard::C == eKey)
    {
        if (m_eState == EPathfindingState::GridUse)
        {
            m_grid.Clear();
        }
    }
    else if (sf::Keyboard::Space == eKey)
    {
        if (m_eState == EPathfindingState::GridUse)
        {
            SetState(EPathfindingState::ExecAlgo);
        }
    }
    else if (sf::Keyboard::F == eKey)
    {
        if (m_eState == EPathfindingState::GridUse)
        {
            m_bPause = !m_bPause;
        }
    }
}

void Pathfinding::OnMouseClicked(int posX, int posY)
{
    if (m_eState == EPathfindingState::GridUse)
    {
        m_grid.OnMouseClicked(posX, posY);
    }
}

void Pathfinding::OnMouseMoved(int posX, int posY)
{
    if (m_eState == EPathfindingState::GridUse)
    {
        m_grid.OnMouseMoved(posX, posY);
    }
}

void Pathfinding::OnMouseReleased()
{
    if (m_eState == EPathfindingState::GridUse)
    {
        m_grid.OnMouseReleased();
    }
}

void Pathfinding::OnDoingOperation(EOperations eOperation, const std::pair<int, int>& vCellCoord)
{
    m_aOperationStack.push_back({ eOperation, vCellCoord });
}
