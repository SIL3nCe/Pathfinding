#include "Pathfinding.h"
#include "imgui.h"
#include "imgui-SFML.h"

using namespace std;

std::vector<SOperation> Pathfinding::m_aOperationStack;

Pathfinding::Pathfinding()
: m_eState(EPathfindingState::GridUse)
, m_grid()
, m_eSelectedAlgo(EAlgorithms::AStar)
, m_algo_Dijkstra()
, m_bDijkstraUseDiagonal(true)
, m_algo_BreadthFirst()
, m_bBreadthFirstUseDiagonal(true)
, m_algo_AStar()
, m_bAStarUseDiagonal(true)
, m_eAStartHeuristic(EHeuristic::Manhattan)
, m_fAStarWeight(1.0f)
, m_currentStep(0)
, m_bRewind(false)
, m_bPause(true)
, m_frameBeforeDrawing(1)
, m_operationsToDrawPerFrames(4)
, m_frameCounter(0)
, m_fTime(0.0f)
, m_steps(0)
, m_fLength(0.0f)
, m_algoClock()
{
    buttonPlay.loadFromFile("Resources\\play.png");
    buttonRewind.loadFromFile("Resources\\playrewind.png");
    buttonPause.loadFromFile("Resources\\pause.png");
    buttonNext.loadFromFile("Resources\\next.png");
    buttonPrevious.loadFromFile("Resources\\previous.png");
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
            m_algoClock.restart();

            GridWorker gridWorker(GRID_SIZE, GRID_SIZE, m_grid.GetStart(), m_grid.GetEnd());
            m_grid.FillGridWorker(&gridWorker);
            vector<pair<int, int>> aPath;

            switch (m_eSelectedAlgo)
            {
                case EAlgorithms::AStar: m_algo_AStar.Execute(gridWorker, m_bAStarUseDiagonal, m_eAStartHeuristic, m_fAStarWeight, aPath, Pathfinding::OnDoingOperation); break;
                case EAlgorithms::Dijksta: m_algo_Dijkstra.Execute(gridWorker, m_bDijkstraUseDiagonal, aPath, Pathfinding::OnDoingOperation); break;
                case EAlgorithms::BreadthFirst: m_algo_BreadthFirst.Execute(gridWorker, m_bBreadthFirstUseDiagonal, aPath, Pathfinding::OnDoingOperation); break;
            }

            m_fLength = m_grid.DrawPath(aPath);

            //Compute stats
            m_fTime = m_algoClock.getElapsedTime().asSeconds();
            m_fTime *= 1000.0f;
            m_steps = m_aOperationStack.size();

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

    m_grid.DrawOperation(m_aOperationStack[m_currentStep]);
    m_currentStep++;

    return false;
}

bool Pathfinding::UndrawAStep()
{
    if (m_currentStep <= 0)
        return true;
    
    //TODO Get last operation and undo it, need to know state of the cell before this op
    
    m_currentStep--;
    m_grid.SetCaseColor(m_aOperationStack[m_currentStep].vCellCoord, sf::Color::White);

    return false;
}

void Pathfinding::DrawGUI()
{
    //Statistics
    if (ImGui::Begin("Stats"))
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
    ImGui::End();

    if (ImGui::Begin("Algorithmes"))
    {
        ImGui::PushItemWidth(100.0f);
        if (EAlgorithms::AStar == m_eSelectedAlgo)
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
                m_eSelectedAlgo = EAlgorithms::AStar;
            }
        }

        if (EAlgorithms::Dijksta == m_eSelectedAlgo)
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
                m_eSelectedAlgo = EAlgorithms::Dijksta;
            }
        }
        
        if (EAlgorithms::BreadthFirst == m_eSelectedAlgo)
        {
            ImGui::SetNextTreeNodeOpen(true);
            if (ImGui::CollapsingHeader("Breadth First"))
            {
                ImGui::Checkbox("Use Diagonal", &m_bBreadthFirstUseDiagonal);
            }
        }
        else
        {
            ImGui::SetNextTreeNodeOpen(false);
            if (ImGui::CollapsingHeader("Breadth First", ImGuiTreeNodeFlags_Bullet))
            {
                m_eSelectedAlgo = EAlgorithms::BreadthFirst;
            }
        }
    }
    ImGui::End();

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
                //TODO
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

    // Global options
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

        ImGui::SliderInt("Frames between operations", &m_frameBeforeDrawing, 1, 10);
        ImGui::SliderInt("Operations per draw", &m_operationsToDrawPerFrames, 1, 20);
    }
    ImGui::End();
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
        {
            m_fTime = 0.0f;
            m_steps = 0;
            m_fLength = 0.0f;
        }
        break;
    }
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
