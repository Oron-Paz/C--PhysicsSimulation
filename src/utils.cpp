#include "../include/utils.hpp"

// vector math functions
float dot(const sf::Vector2f &v1, const sf::Vector2f &v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

float magnitude_squared(sf::Vector2f &v)
{
    return v.x * v.x + v.y * v.y;
}

// kinematics functions
void handle_boundary_collision(float &pos, float &vel, float min_bound, float max_bound)
{
    if (pos > max_bound)
    {
        pos = max_bound;
        vel = -vel * DAMP_FACTOR;
    }
    if (pos < min_bound)
    {
        pos = min_bound;
        vel = -vel * DAMP_FACTOR;
    }
}

void apply_gravity(sf::Vector2f &position, sf::Vector2f &velocity, sf::CircleShape &shape, float deltaTime)
{
    // Update position based on current velocity
    position += velocity * deltaTime;

    // Apply gravity to vertical velocity
    velocity.y += GLOBAL_CONST_GRAVITY * deltaTime;

    float shapeRadius = shape.getRadius();
    handle_boundary_collision(position.y, velocity.y, shapeRadius, HEIGHT - shapeRadius);
    handle_boundary_collision(position.x, velocity.x, shapeRadius, WIDTH - shapeRadius);

    shape.setPosition(position);
}

void collide(CircleObject &thisShape, CircleObject &otherShape)
{
    const float EPSILON = 1e-5f;
    if (detect_collisions(thisShape.getShape(), otherShape.getShape()))
    {
        sf::Vector2f v1 = thisShape.getVelocity();
        sf::Vector2f v2 = otherShape.getVelocity();
        sf::Vector2f x1 = thisShape.getShape().getPosition();
        sf::Vector2f x2 = otherShape.getShape().getPosition();

        sf::Vector2f x_diff = x1 - x2;
        float x_diff_mag_sq = magnitude_squared(x_diff);

        if (x_diff_mag_sq < EPSILON)
            return; // Avoid division by zero

        sf::Vector2f v_diff = v1 - v2;
        float scalar = dot(v_diff, x_diff) / x_diff_mag_sq;

        // Adjust velocities based on impulse
        sf::Vector2f impulse = x_diff * scalar;
        thisShape.setVelocity((v1 - impulse) * DAMP_FACTOR);
        otherShape.setVelocity((v2 + impulse) * DAMP_FACTOR);

        // Adjust positions to prevent sticking
        float radiiSum = thisShape.getShape().getRadius() + otherShape.getShape().getRadius();
        float distance = std::sqrt(x_diff_mag_sq);
        float overlap = radiiSum - distance;

        if (overlap > 0)
        { // Only adjust if there's actual overlap
            sf::Vector2f separation = x_diff / distance * overlap * 0.5f;

            // Move shapes apart
            thisShape.setPosition(x1 + separation);
            otherShape.setPosition(x2 - separation);
        }
    }
}

bool detect_collisions(const sf::CircleShape &thisShape, const sf::CircleShape &otherShape)
{
    sf::Vector2f thisPos = thisShape.getPosition();
    sf::Vector2f otherPos = otherShape.getPosition();
    float radiiSum = thisShape.getRadius() + otherShape.getRadius();
    float x_diff = thisPos.x - otherPos.x;
    float y_diff = thisPos.y - otherPos.y;
    float distance = std::sqrt(x_diff * x_diff + y_diff * y_diff);
    return distance < radiiSum;
}