#include <SFML/Graphics.hpp>

#include "Grid.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pathfinding");

    Grid grid;
    grid.Initialize();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case  sf::Event::MouseButtonPressed:
                {
                    grid.OnMouseClicked(event.mouseButton.x, event.mouseButton.y);
                }
                break;

                case sf::Event::MouseMoved:
                {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        grid.OnMouseMoved(event.mouseMove.x, event.mouseMove.y);
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

        window.clear();

        grid.Draw(window);

        window.display();
    }

    return 0;
}
