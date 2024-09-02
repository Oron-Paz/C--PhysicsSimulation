#ifndef KINEMATICS_H
#define KINEMATICS_H

#include <SFML/Graphics.hpp>
#include "CircleObject.h"

class CircleObject;

namespace constants
{
    const float GLOBAL_CONST_GRAVITY = 980.0f;
    const float DAMP_FACTOR = 0.8f;
    // ... other related constants
} // namespace constants

void apply_gravity(sf::Vector2f& position, sf::Vector2f& velocity, sf::CircleShape& shape, float deltaTime);
void collide(CircleObject& thisShape, CircleObject& otherShape);
bool detect_collisions(const sf::CircleShape& thisShape, const sf::CircleShape& otherShape);

#endif // KINEMATICS_H
