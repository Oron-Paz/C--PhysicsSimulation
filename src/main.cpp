#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include "../include/utils.hpp"
#include "../include/menu.hpp"

enum class SimulationState
{
    MENU,
    RUNNING_SIMULATION,
    EXIT
};

int main()
{
    SimulationState state = SimulationState::MENU;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Physics Simulation");
    sf::Clock clock; // Starts the clock

    // Initialize random seed
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::vector<CircleObject> circles(200);

    Menu menu;

    while (window.isOpen())
    {
        sf::Event event;
        sf::Time deltaTime = clock.restart(); // Restart clock and get deltaTime
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    menu.moveUp();
                    break;
                case sf::Keyboard::Down:
                    menu.moveDown();
                    break;
                case sf::Keyboard::Return:
                    switch (menu.getSelectedItemIndex())
                    {
                    case 0:
                        state = SimulationState::RUNNING_SIMULATION;
                        for (std::size_t i = 0; i < circles.size(); ++i)
                        {
                            float x = std::rand() % WIDTH;
                            float y = std::rand() % HEIGHT;
                            circles[i] = CircleObject(RADIUS, sf::Color::Blue, sf::Vector2f(x, y));
                        }
                        break;
                    case 1:
                        // Choose number of circles and start simulation
                        break;
                    case 2:
                        state = SimulationState::EXIT;
                        window.close();
                        break;
                    default:
                        break;
                    }
                    break;
                case sf::Keyboard::M:
                    state = SimulationState::MENU;
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        if (state == SimulationState::RUNNING_SIMULATION)
        {
            for (std::size_t i = 0; i < circles.size(); ++i)
            {
                circles[i].update(deltaTime.asSeconds());

                // Check for collisions with other circles
                for (std::size_t j = i + 1; j < circles.size(); ++j)
                {
                    collide(circles[i], circles[j]);
                }
            }

            // Draw each circle
            for (auto &circle : circles)
            {
                circle.draw(window);
            }
        }
        else if (state == SimulationState::MENU)
        {
            menu.draw(window);
        }
        window.display();
    }

    return 0;
}
