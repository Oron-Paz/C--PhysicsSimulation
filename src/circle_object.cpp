#include "../include/circle_object.hpp"

CircleObject::CircleObject(int radius, sf::Color color, sf::Vector2f position) // Constructor
    : color(color), shape(radius), position(position), velocity(0, 0)
{
    shape.setPosition(position);
    shape.setFillColor(color);
}

CircleObject::CircleObject()
    : color(sf::Color::White), shape(0), position(0, 0), velocity(0, 0)
{
    shape.setPosition(position);
    shape.setFillColor(color);
}

void CircleObject::draw(sf::RenderWindow &window)
{ // Pass window by reference, draws on window
    window.draw(shape);
}

void CircleObject::update(float deltaTime)
{
    apply_gravity(position, velocity, shape, deltaTime);
}

void CircleObject::update_without_gravity(float deltaTime)
{
    position += velocity * deltaTime;
    // Boundary collision
    if (position.y > HEIGHT - shape.getRadius() * 2)
    {
        position.y = HEIGHT - shape.getRadius() * 2;
        velocity.y = -velocity.y;
    }
    if (position.y < 0 + shape.getRadius() * 2)
    {
        position.y = 0 + shape.getRadius() * 2;
        velocity.y = -velocity.y;
    }
    if (position.x > WIDTH - shape.getRadius() * 2)
    {
        position.x = WIDTH - shape.getRadius() * 2;
        velocity.x = -velocity.x;
    }
    if (position.x < 0 + shape.getRadius() * 2)
    {
        position.x = 0 + shape.getRadius() * 2;
        velocity.x = -velocity.x;
    }
    shape.setPosition(position);
}
