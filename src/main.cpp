#include <SFML/Graphics.hpp>

#include "Grid.h"

#include "Pathfinding.h"
#include "Dijkstra.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Pathfinding");

    Grid grid;
    grid.Initialize();

    Dijkstra algo;
    algo.Initialize(grid);

    while (window.isOpen())
    {
        bool bMouseButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::KeyPressed:
                {
                    if (sf::Keyboard::R == event.key.code && !bMouseButtonPressed)
                    {
                        grid.Reset();
                    }
                    else if (sf::Keyboard::Space == event.key.code && !bMouseButtonPressed)
                    {
                        algo.Execute();
                    }
                }
                break;

                case  sf::Event::MouseButtonPressed:
                {
                    grid.OnMouseClicked(event.mouseButton.x, event.mouseButton.y);
                }
                break;

                case sf::Event::MouseMoved:
                {
                    if (bMouseButtonPressed)
                    {
                        grid.OnMouseMoved(event.mouseMove.x, event.mouseMove.y);
                    }
                }
                break;

                case sf::Event::MouseButtonReleased:
                {
                    grid.OnMouseReleased();
                }
                break;

                case sf::Event::Closed:
                {
                    window.close();
                }
                break;
            }
        }

        window.clear();

        grid.Draw(window);

        window.display();
    }

    return 0;
}
