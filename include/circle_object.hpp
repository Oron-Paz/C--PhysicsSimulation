#ifndef CIRCLE_OBJECT_HPP
#define CIRCLE_OBJECT_HPP

#include <SFML/Graphics.hpp>
#include "utils.hpp"

class CircleObject
{
public:
    CircleObject(int radius, sf::Color color, sf::Vector2f position);   // Constructor
    CircleObject();                                                     // Default constructor
    void draw(sf::RenderWindow &window);                                // Pass window by reference
    void update(float deltaTime);                                       // Update function to apply gravity);
    void update_without_gravity(float deltaTime);                            // Update function without gravity

    // TODO:  get/set in header file but need to look at the efficiency of this
    const sf::CircleShape getShape() const { return shape; }
    const sf::Vector2f getPosition() const { return position; }
    const sf::Vector2f getVelocity() const { return velocity; }
    void setPosition(sf::Vector2f position) { this->position = position; }
    void setVelocity(sf::Vector2f velocity) { this->velocity = velocity; }

private:
    // int radius;
    sf::Color color;
    sf::CircleShape shape;
    sf::Vector2f position;
    sf::Vector2f velocity;
};

#endif // CIRCLE_OBJECT_HPP
