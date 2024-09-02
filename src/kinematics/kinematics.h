#ifndef KINEMATICS_H
#define KINEMATICS_H

#include <SFML/Graphics.hpp>

namespace constants
{
    const float GLOBAL_CONST_GRAVITY = 980.0f;
    const float DAMP_FACTOR = 0.8f;
    // ... other related constants

} // namespace constants

void apply_gravity(sf::Vector2f& position, sf::Vector2f& velocity, sf::CircleShape& shape , float deltaTime);
bool detect_collisions(sf::CircleShape& thisShape, sf::CircleShape& otherShape);

#endif //KINEMATICS_H