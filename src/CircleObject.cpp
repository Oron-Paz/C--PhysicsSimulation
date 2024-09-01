#include "CircleObject.h"

CircleObject::CircleObject(int radius, sf::Color color, sf::Vector2f position )  // Constructor
    : radius(radius), color(color), shape(radius) ,position(position), velocity(0, 0) {
    shape.setPosition(position);
    shape.setFillColor(color);
}

void CircleObject::draw(sf::RenderWindow& window) { // Pass window by reference, draws on window
    window.draw(shape);
}

void CircleObject::update(float deltaTime) {
    ::apply_gravity(position, velocity, shape, deltaTime);
}


