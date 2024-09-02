#include <SFML/Graphics.hpp>
#include "CircleObject.h"
#include "kinematics/kinematics.h"
#include "utils/vectorMath.h"
#include <iostream>

#define WIDTH 1280
#define HEIGHT 720

#define RADIUS 5             // Radius of the circle  

#define  NUM_ROWS  5        // Number of rows in the grid
#define  NUM_COLS  30        // Number of columns in the grid
#define  SPACING  5.0f    // Spacing between circles

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "PHYSICS SIMULATOR");
    sf::Clock clock; // starts the clock

    CircleObject circles[NUM_ROWS][NUM_COLS];

    // Initialize the circles
    for (int row = 0; row < NUM_ROWS; ++row) {
        for (int col = 0; col < NUM_COLS; ++col) {
            // Calculate the position for each circle
            float x = 100 + col * (2 * RADIUS + SPACING);
            float y = 100 + row * (2 * RADIUS + SPACING);
            // Create and initialize each circle
            circles[row][col] = CircleObject(RADIUS, sf::Color::Blue, sf::Vector2f(x, y));
        }
    }

    circles[4][5].setPosition(sf::Vector2f(500, 0));



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


        // Check for collisions
        for (int row1 = 0; row1 < NUM_ROWS; ++row1) {
            for (int col1 = 0; col1 < NUM_COLS; ++col1) {
                for (int row2 = row1; row2 < NUM_ROWS; ++row2) {
                    for (int col2 = (row2 == row1 ? col1 + 1 : 0); col2 < NUM_COLS; ++col2) {
                        collide(circles[row1][col1], circles[row2][col2]);
                    }
                }
            }
        }

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