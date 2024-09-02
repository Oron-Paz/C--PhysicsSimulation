#include <SFML/Graphics.hpp>
#include "CircleObject.h"
#include "kinematics/kinematics.h"
#include <iostream>

#define WIDTH 1280
#define HEIGHT 720

#define RADIUS 25              // Radius of the circle  

#define  NUM_ROWS  2         // Number of rows in the grid
#define  NUM_COLS  1        // Number of columns in the grid
#define  SPACING  10.0f    // Spacing between circles

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "PHYSICS SIMULATOR");
    sf::Clock clock; // starts the clock

    CircleObject circles[NUM_ROWS][NUM_COLS];

    // Initialize the circles
    /*for (int row = 0; row < NUM_ROWS; ++row) {
        for (int col = 0; col < NUM_COLS; ++col) {
            // Calculate the position for each circle
            float x = 100 + col * (2 * RADIUS + SPACING);
            float y = 100 + row * (2 * RADIUS + SPACING);
            // Create and initialize each circle
            circles[row][col] = CircleObject(RADIUS, sf::Color::Blue, sf::Vector2f(x, y));
        }
    }*/

    circles[0][0] = CircleObject(RADIUS, sf::Color::Blue, sf::Vector2f(100, 100));
    circles[1][0] = CircleObject(RADIUS, sf::Color::Red, sf::Vector2f(100, 200));


    while (window.isOpen())
    {
        sf::Event event;
        sf::Time deltaTime = clock.restart(); // Restart clock and get deltaTime

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

       // Update each circle
        for (int row = 0; row < NUM_ROWS; ++row) {
            for (int col = 0; col < NUM_COLS; ++col) {
                circles[row][col].update(deltaTime.asSeconds());
            }
        }
       
        collide(circles[0][0], circles[1][0]);

        window.clear();

        // Draw each circle
        for (int row = 0; row < NUM_ROWS; ++row) {
            for (int col = 0; col < NUM_COLS; ++col) {
                circles[row][col].draw(window);
            }
        }
        window.display();
    }

    return 0;
}