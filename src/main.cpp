#include "imgui.h"
#include "imgui-SFML.h"

#include "Grid.h"

#include "Algo/Pathfinding.h"
#include "Algo/Dijkstra.h"
#include "Algo/BreadthFirst.h"
#include "Algo/AStar.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Pathfinding");
    window.setFramerateLimit(60);

    ImGui::SFML::Init(window);

    sf::Font font;
    if (!font.loadFromFile("Resources\\Gold-Regular.ttf"))
    {
        printf("Cannot load font");
    }

    // Init grid
    Grid grid;
    grid.Initialize();

    // Init algos
    Dijkstra algo_Dijkstra;
    BreadthFirst algo_BreadthFirst;
    AStar algo_AStart;

    std::vector<Pathfinding*> aAlgo;
    aAlgo.push_back(&algo_AStart);
    aAlgo.push_back(&algo_Dijkstra);
    aAlgo.push_back(&algo_BreadthFirst);

    for (Pathfinding* pAlgo : aAlgo)
    {
        pAlgo->Initialize(grid, font);
    }

    Pathfinding* pCurrentAlgo = aAlgo[0];
    pCurrentAlgo->m_bGuiOpen = true;

    bool bExecAlgo = false;
    bool bPause = false;

    // Time datas for async exec
    float fAlgoExecTime = 0.01f;
    float fAlgoExecDt = 0.5f;

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time dtTime = clock.restart();
        float dt = dtTime.asSeconds();

        bool bMouseButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            switch (event.type)
            {
                case sf::Event::KeyPressed:
                {
                    if (sf::Keyboard::R == event.key.code && !bMouseButtonPressed && !bExecAlgo)
                    {
                        grid.Reset();
                        pCurrentAlgo->Clear();
                    }  
                    else if (sf::Keyboard::C == event.key.code && !bMouseButtonPressed && !bExecAlgo)
                    {
                        grid.Clear();
                        pCurrentAlgo->Clear();
                    }
                    else if (sf::Keyboard::Space == event.key.code && !bMouseButtonPressed)
                    {
                        // Start
                        if (!bExecAlgo && !bPause)
                        {
                            bExecAlgo = true;
                            grid.Clear();

                            // Select algo to execute (first found with gui open)
                            for (Pathfinding* pAlgo : aAlgo)
                            {
                                if (pAlgo->m_bGuiOpen)
                                {
                                    pCurrentAlgo = pAlgo;
                                    break;
                                }
                            }

                            pCurrentAlgo->Clear();
                            pCurrentAlgo->Start();
                        }
                        // Unpause
                        else if (bPause)
                        {
                            bExecAlgo = true;
                            bPause = false;
                        }
                        // Pause
                        else
                        {
                            bExecAlgo = false;
                            bPause = true;
                        }
                    }
                    else if (sf::Keyboard::Escape == event.key.code && (bExecAlgo || bPause))
                    {
                        bExecAlgo = false;
                        grid.Clear();
                        pCurrentAlgo->Clear();
                    }
                }
                break;

                case  sf::Event::MouseButtonPressed:
                {
                    if (!bExecAlgo)
                    {
                        grid.OnMouseClicked(event.mouseButton.x, event.mouseButton.y);
                    }
                }
                break;

                case sf::Event::MouseMoved:
                {
                    if (!bExecAlgo)
                    {
                        if (bMouseButtonPressed)
                        {
                            grid.OnMouseMoved(event.mouseMove.x, event.mouseMove.y);
                        }
                    }
                }
                break;

                case sf::Event::MouseButtonReleased:
                {
                    if (!bExecAlgo)
                    {
                        grid.OnMouseReleased();
                    }
                }
                break;

                case sf::Event::Closed:
                {
                    window.close();
                }
                break;
            }
        }

        if (bExecAlgo)
        {
            fAlgoExecDt += dt;
            if (fAlgoExecDt >= fAlgoExecTime)
            {
                fAlgoExecDt = 0.0f;
                if (bExecAlgo = pCurrentAlgo->Execute(), !bExecAlgo)
                {
                    pCurrentAlgo->Stop();
                }
            }
        }
        
        ImGui::SFML::Update(window, dtTime);

        pCurrentAlgo->DrawGuiStatistics();

        if (ImGui::Begin("Algorithmes"))
        {
            for (Pathfinding* pAlgo : aAlgo)
            {
                pAlgo->DrawGui();
            }
            ImGui::End();
        }

        // Global options
        if (ImGui::Begin("Options"))
        {
            ImGui::SliderFloat("Animation Speed", &fAlgoExecTime, 0.001f, 0.1f);
            ImGui::End();
        }

        window.clear();

        grid.Draw(window);
        pCurrentAlgo->Draw(window);

        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}
