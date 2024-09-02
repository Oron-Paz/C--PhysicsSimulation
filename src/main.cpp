#include <SFML/Graphics.hpp>
#include "CircleObject.h"
#include "kinematics/kinematics.h"
#include "utils/vectorMath.h"
#include <iostream>

#define WIDTH 1280
#define HEIGHT 720

#define RADIUS 5             // Radius of the circle  

#define NUM_ROWS 10           // Number of rows in the grid
#define NUM_COLS 30          // Number of columns in the grid
#define SPACING 5.0f         // Spacing between circles

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "PHYSICS SIMULATOR");
    sf::Clock clock; // Starts the clock

    // Initialize random seed
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::vector<CircleObject> circles;

    std::cout << "Would you like: " << std::endl;
    std::cout << "[1] 100 Balls in random positions:\n";
    std::cout << "[2] Random Ball positions (set count):\n";
    std::cout << "[3] Rectangle Ball positions (set rows & columns):\n";

    int choice;
    std::cin >> choice;

    if (choice == 1) {
        circles.resize(100);
        for (int i = 0; i < 100; ++i) {
            float x = std::rand() % WIDTH;
            float y = std::rand() % HEIGHT;
            circles[i] = CircleObject(RADIUS, sf::Color::Blue, sf::Vector2f(x, y));
        }
    } else if (choice == 2) {
        std::cout << "How many balls? " << std::endl;
        int count;
        std::cin >> count;
        circles.resize(count);
        for (int i = 0; i < count; ++i) {
            float x = std::rand() % WIDTH;
            float y = std::rand() % HEIGHT;
            circles[i] = CircleObject(RADIUS, sf::Color::Blue, sf::Vector2f(x, y));
        }
    } else if (choice == 3) {
        std::cout << "How many rows? " << std::endl;
        int rows;
        std::cin >> rows;
        std::cout << "How many columns? " << std::endl;
        int cols;
        std::cin >> cols;
        circles.reserve(rows * cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                float x = 100 + j * (2 * RADIUS + SPACING);
                float y = 100 + i * (2 * RADIUS + SPACING);
                circles.emplace_back(RADIUS, sf::Color::Blue, sf::Vector2f(x, y));
            }
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        sf::Time deltaTime = clock.restart(); // Restart clock and get deltaTime

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Update and handle collisions
        for (size_t i = 0; i < circles.size(); ++i) {
            circles[i].update(deltaTime.asSeconds());

             // Check for collisions with other circles
             for (size_t j = i + 1; j < circles.size(); ++j) {
                collide(circles[i], circles[j]);
            }
        }

        // Draw each circle
        for (auto& circle : circles) {
            circle.draw(window);
        }

        window.display();
    }

    return 0;
}
