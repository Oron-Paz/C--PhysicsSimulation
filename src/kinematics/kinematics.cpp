#include "kinematics.h"
#include <iostream>
#include <cmath>
#include "../utils/vectorMath.h"

void apply_gravity(sf::Vector2f& position, sf::Vector2f& velocity, sf::CircleShape& shape, float deltaTime) {
    position.y += velocity.y * deltaTime;
    velocity.y += constants::GLOBAL_CONST_GRAVITY * deltaTime;
    shape.setPosition(position);

    if (position.y > 720 - shape.getRadius() * 2) {
        position.y = 720 - shape.getRadius() * 2;
        velocity.y = -velocity.y * constants::DAMP_FACTOR;
    }
    if (position.y < 0 + shape.getRadius() * 2) {
        position.y = 0 + shape.getRadius() * 2;
        velocity.y = -velocity.y * constants::DAMP_FACTOR;
    }
    if (position.x > 1280 - shape.getRadius() * 2) {
        position.x = 1280 - shape.getRadius() * 2;
        velocity.x = -velocity.x * constants::DAMP_FACTOR;
    }
    if (position.x < 0 + shape.getRadius() * 2) { 
        position.x = 0 + shape.getRadius() * 2;
        velocity.x = -velocity.x * constants::DAMP_FACTOR;
    }
}

void collide(CircleObject& thisShape, CircleObject& otherShape) {
    if (detect_collisions(thisShape.getShape(), otherShape.getShape())) {
        sf::Vector2f v1 = thisShape.getVelocity();
        sf::Vector2f v2 = otherShape.getVelocity();
        sf::Vector2f x1 = thisShape.getShape().getPosition();
        sf::Vector2f x2 = otherShape.getShape().getPosition();

        sf::Vector2f x_diff = x1 - x2;
        float x_diff_mag_sq = magnitude_squared(x_diff);

        sf::Vector2f v_diff = v1 - v2;

        //simplified scalar calculation (mass terms cancel as mass=1 always)
        float scalar = dot(v_diff, x_diff) / x_diff_mag_sq;

        sf::Vector2f new_v1 = v1 - sf::Vector2f(x_diff.x * scalar, x_diff.y * scalar);
        sf::Vector2f new_v2 = v2 + sf::Vector2f(x_diff.x * scalar, x_diff.y * scalar);

        thisShape.setVelocity(new_v1);
        otherShape.setVelocity(new_v2);


        //honeslty no clue what this part does this is all chatGPT down here
        // Separate the objects to prevent sticking
        float overlap = thisShape.getShape().getRadius() + otherShape.getShape().getRadius() - 
                        std::sqrt(x_diff_mag_sq);
        sf::Vector2f separation = sf::Vector2f(x_diff.x * overlap / (2*std::sqrt(x_diff_mag_sq)),
                                               x_diff.y * overlap / (2*std::sqrt(x_diff_mag_sq)));
        thisShape.setPosition(x1 + separation);
        otherShape.setPosition(x2 - separation);
    }
}

bool detect_collisions(const sf::CircleShape& thisShape, const sf::CircleShape& otherShape) {
    sf::Vector2f thisPosition = thisShape.getPosition();
    sf::Vector2f otherPosition = otherShape.getPosition();
    float thisRadius = thisShape.getRadius();
    float otherRadius = otherShape.getRadius();

    // Calculate the difference in positions
    sf::Vector2f difference = otherPosition - thisPosition;

    // Calculate the distance between the centers using the Euclidean distance formula
    float distance = std::sqrt(difference.x * difference.x + difference.y * difference.y);

    // Check if distance is less than or equal to the sum of the radii
    return (distance <= (thisRadius + otherRadius));
}
