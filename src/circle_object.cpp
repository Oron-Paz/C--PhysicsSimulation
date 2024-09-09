#include "../include/circle_object.hpp"

CircleObject::CircleObject(int radius, sf::Color color, sf::Vector2f position) // Constructor
    : color(color), shape(radius), position(position), velocity(0, 0)
{
    shape.setOrigin(radius, radius);
    shape.setPosition(position);
    shape.setFillColor(color);
}

CircleObject::CircleObject() : color(sf::Color::White), shape(0), position(0, 0), velocity(0, 0)
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
    int shapeRadius = shape.getRadius();
    // Boundary collision
    if (position.y > HEIGHT - shapeRadius)
    {
        position.y = HEIGHT - shapeRadius;
        velocity.y = -velocity.y;
    }
    if (position.y < shapeRadius)
    {
        position.y = shapeRadius;
        velocity.y = -velocity.y;
    }
    if (position.x > WIDTH - shapeRadius)
    {
        position.x = WIDTH - shapeRadius;
        velocity.x = -velocity.x;
    }
    if (position.x < shapeRadius)
    {
        position.x = shapeRadius;
        velocity.x = -velocity.x;
    }
    shape.setPosition(position);
}
