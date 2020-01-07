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
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        grid.Draw(window);

        window.display();
    }

    return 0;
}
