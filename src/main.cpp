#include <SFML/Graphics.hpp>
#include "CircleObject.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "PHYSICS SIMULATOR");
    sf::Clock clock; // starts the clock
    CircleObject circle(50, sf::Color::Blue, sf::Vector2f(100, 100)); //create circle (radius, color, position)

    while (window.isOpen())
    {
        sf::Event event;
        sf::Time deltaTime = clock.restart(); // Restart clock and get deltaTime

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //sf::Time elapsed1 = clock.getElapsedTime();
        //std::cout << elapsed1.asSeconds() << std::endl;
        circle.update(deltaTime.asSeconds());

        window.clear();
        circle.draw(window);
        window.display();
    }

    return 0;
}