#include "kinematics.h"
#include <iostream>

void apply_gravity(sf::Vector2f& position, sf::Vector2f& velocity, sf::CircleShape& shape, float deltaTime) {
    position.y += velocity.y * deltaTime;
    velocity.y += constants::GLOBAL_CONST_GRAVITY * deltaTime;
    shape.setPosition(position);
    

    if (position.y > 720 - shape.getRadius() * 2) {
        position.y = 720 - shape.getRadius() * 2;
        velocity.y = -velocity.y * constants::DAMP_FACTOR;
    }
    if(position.y < 0 + shape.getRadius() * 2){
        position.y = 0 + shape.getRadius() * 2;
        velocity.y = -velocity.y * constants::DAMP_FACTOR;
    }
    if(position.x > 1280 - shape.getRadius() * 2){
        position.x = 1280 - shape.getRadius() * 2;
        velocity.x = -velocity.x * constants::DAMP_FACTOR;
    }
    if (position.x < 0 + shape.getRadius() * 2){ 
        position.x = 0 + shape.getRadius() * 2;
        velocity.x = -velocity.x * constants::DAMP_FACTOR;
    }
}

