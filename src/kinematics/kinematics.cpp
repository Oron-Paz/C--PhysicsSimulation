#include "kinematics.h"

void apply_gravity(sf::Vector2f& position, sf::Vector2f& velocity, sf::CircleShape& shape, float deltaTime) {
    position.y += velocity.y * deltaTime;
    velocity.y += constants::GLOBAL_CONST_GRAVITY * deltaTime;
    shape.setPosition(position);
}


