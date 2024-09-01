#ifndef KINEMATICS_H
#define KINEMATICS_H

#include <SFML/Graphics.hpp>

namespace constants
{
    const float GLOBAL_CONST_GRAVITY = 200.0f;
    // ... other related constants

} // namespace constants

void apply_gravity(sf::Vector2f& position, sf::Vector2f& velocity, sf::CircleShape& shape , float deltaTime);

#endif //KINEMATICS_H