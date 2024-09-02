#include "kinematics.h"
#include <iostream>
#include <cmath>
#include "../utils/vectorMath.h"

void apply_gravity(sf::Vector2f& position, sf::Vector2f& velocity, sf::CircleShape& shape, float deltaTime) {
    position.y += velocity.y * deltaTime;
    velocity.y += constants::GLOBAL_CONST_GRAVITY * deltaTime;

    if (position.y > 720 - shape.getRadius() * 2 + 2) {
        position.y = 720 - shape.getRadius() * 2 + 2;
        velocity.y = -velocity.y * constants::DAMP_FACTOR;
    }
    if (position.y < 0 + shape.getRadius() * 2 + 2) {
        position.y = 0 + shape.getRadius() * 2 + 2;
        velocity.y = -velocity.y * constants::DAMP_FACTOR;
    }
    if (position.x > 1280 - shape.getRadius() * 2 + 2) {
        position.x = 1280 - shape.getRadius() * 2 + 2;
        velocity.x = -velocity.x * constants::DAMP_FACTOR;
    }
    if (position.x < 0 + shape.getRadius() * 2 + 2) { 
        position.x = 0 + shape.getRadius() * 2 + 2;
        velocity.x = -velocity.x * constants::DAMP_FACTOR;
    }

    shape.setPosition(position);
}

void collide(CircleObject& thisShape, CircleObject& otherShape) {
    if (detect_collisions(thisShape.getShape(), otherShape.getShape())) {
        sf::Vector2f v1 = thisShape.getVelocity();
        sf::Vector2f v2 = otherShape.getVelocity();
        sf::Vector2f x1 = thisShape.getShape().getPosition();
        sf::Vector2f x2 = otherShape.getShape().getPosition();

        sf::Vector2f x_diff = x1 - x2;
        float x_diff_mag_sq = magnitude_squared(x_diff);

        if (x_diff_mag_sq == 0) return; // Avoid division by zero

        sf::Vector2f v_diff = v1 - v2;
        float scalar = dot(v_diff, x_diff) / x_diff_mag_sq;

        // Adjust velocities
        sf::Vector2f impulse = x_diff * scalar;
        sf::Vector2f new_v1 = v1 - impulse;
        sf::Vector2f new_v2 = v2 + impulse;

        thisShape.setVelocity(new_v1);
        otherShape.setVelocity(new_v2);

        // Adjust positions to prevent sticking
        float overlap = thisShape.getShape().getRadius() + otherShape.getShape().getRadius() - 
                        std::sqrt(x_diff_mag_sq);

        if (overlap > 0) { // Only adjust if there's actual overlap
            sf::Vector2f separation = x_diff * (overlap / std::sqrt(x_diff_mag_sq)) * 0.5f;

            // Move shapes apart
            thisShape.setPosition(x1 + separation);
            otherShape.setPosition(x2 - separation);
        }
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
