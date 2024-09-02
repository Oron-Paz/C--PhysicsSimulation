#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "../include/utils.hpp"
#include "../include/main_menu.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "PHYSICS SIMULATOR");
    sf::Clock clock; // Starts the clock

    // Initialize random seed
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::vector<CircleObject> circles(1000);

    for (int i = 0; i < 1000; ++i)
    {
        float x = std::rand() % WIDTH;
        float y = std::rand() % HEIGHT;
        circles[i] = CircleObject(RADIUS, sf::Color::Blue, sf::Vector2f(x, y));
    }

    MainMenu mainMenu;
    mainMenu.setSimulationState(SimulationState::MENU);

    while (mainMenu.getSimulationState() == SimulationState::MENU)
    {
        mainMenu.handleInput(window);
        mainMenu.update(clock.getElapsedTime().asSeconds());
        mainMenu.draw(window);
        window.display();
    }

    while (window.isOpen())
    {
        sf::Event event;
        sf::Time deltaTime = clock.restart(); // Restart clock and get deltaTime

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Update and handle collisions
        for (size_t i = 0; i < circles.size(); ++i)
        {
            circles[i].update(deltaTime.asSeconds());

            // Check for collisions with other circles
            for (size_t j = i + 1; j < circles.size(); ++j)
            {
                collide(circles[i], circles[j]);
            }
        }

        // Draw each circle
        for (auto &circle : circles)
        {
            circle.draw(window);
        }

        window.display();
    }

    return 0;
}
