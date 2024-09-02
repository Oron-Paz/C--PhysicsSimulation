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

bool detect_collisions(sf::CircleShape& thisShape, sf::CircleShape& otherShape) {
    sf::Vector2f thisPosition = thisShape.getPosition();
    sf::Vector2f otherPosition = otherShape.getPosition();
    float thisRadius = thisShape.getRadius();
    float otherRadius = otherShape.getRadius();

    // Calculate the difference in positions
    sf::Vector2f difference = otherPosition - thisPosition;

    // Calculate the distance between the centers using the Euclidean distance formula
    float distance = std::sqrt(difference.x * difference.x + difference.y * difference.y);

    //std::cout << "Distance between centers = " << distance << std::endl;

    // Check if distance is less than or equal to the sum of the radii
    if (distance <= (thisRadius + otherRadius)) {
        return true; // collision detected
    }

    return false; // collision not detected
}
