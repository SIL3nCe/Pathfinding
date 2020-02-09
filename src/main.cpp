#include <SFML/Graphics.hpp>

#include "imgui.h"

#include "Grid.h"

#include "Algo/Pathfinding.h"
#include "Algo/Dijkstra.h"
#include "Algo/BreadthFirst.h"
#include "Algo/AStar.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Pathfinding");

    sf::Font font;
    if (!font.loadFromFile("Resources\\Gold-Regular.ttf"))
    {
        printf("Pathfinding::Initialize Cannot load font");
    }

    Grid grid;
    grid.Initialize();

    //Dijkstra algo;
    //Dijkstra algo;
    //BreadthFirst algo;
    AStar algo;
    algo.Initialize(grid, font);

    bool bExecAlgo = false;
    float fAlgoExecTime = 0.01f;
    float fAlgoExecDt = 0.5f;

    sf::Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        bool bMouseButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::KeyPressed:
                {
                    if (sf::Keyboard::R == event.key.code && !bMouseButtonPressed && !bExecAlgo)
                    {
                        grid.Reset();
                        algo.Clear();
                    }  
                    else if (sf::Keyboard::C == event.key.code && !bMouseButtonPressed && !bExecAlgo)
                    {
                        grid.Clear();
                        algo.Clear();
                    }
                    else if (sf::Keyboard::Space == event.key.code && !bMouseButtonPressed)
                    {
                        //TODO pause when hitting space again, add bool to know if need to clear
                        if (!bExecAlgo)
                        {
                            bExecAlgo = true;
                            grid.Clear();
                            algo.Clear();
                            algo.Start();
                        }
                    }
                    else if (sf::Keyboard::Escape == event.key.code && bExecAlgo)
                    {
                        bExecAlgo = false;
                        grid.Clear();
                        algo.Clear();
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
                if (bExecAlgo = algo.Execute(), !bExecAlgo)
                {
                    algo.Stop();
                }
            }
        }

        window.clear();

        grid.Draw(window);
        algo.Draw(window);

        window.display();
    }

    return 0;
}
