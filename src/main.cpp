#include "imgui.h"
#include "imgui-SFML.h"

#include "Pathfinding.h"

using namespace std;

/*TODO
    -nbr de cases dynamique
    -Trouver autre solution plus opti pour le gridworker
*ALGOs
    -Gérer bidirectionnel
    -Implem plus d'algo
*/

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Pathfinding");
    //window.setFramerateLimit(120);

    ImGui::SFML::Init(window);
    ImGuiIO& io = ImGui::GetIO();

    Pathfinding pathfinding;

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time dtTime = clock.restart();
        float dt = dtTime.asSeconds();

        bool bMouseButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left) && !io.WantCaptureMouse;

        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            switch (event.type)
            {
                case sf::Event::KeyPressed:
                {
                    if (!bMouseButtonPressed)
                    {
                        pathfinding.OnKeyPressed(event.key.code);
                    }
                }
                break;

                case  sf::Event::MouseButtonPressed:
                {
                    if (bMouseButtonPressed)
                    {
                        pathfinding.OnMouseClicked(event.mouseButton.x, event.mouseButton.y);
                    }
                }
                break;

                case sf::Event::MouseMoved:
                {
                    if (bMouseButtonPressed)
                    {
                        pathfinding.OnMouseMoved(event.mouseMove.x, event.mouseMove.y);
                    }
                }
                break;

                case sf::Event::MouseButtonReleased:
                {
                    pathfinding.OnMouseReleased();
                }
                break;

                case sf::Event::Closed:
                {
                    window.close();
                }
                break;
            }
        }

        ImGui::SFML::Update(window, dtTime);
        
        pathfinding.Update(dt);

        window.clear();

        //ImGui::ShowDemoWindow();

        pathfinding.Draw(window);

        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}
