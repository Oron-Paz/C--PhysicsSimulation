#ifndef UTILS_HPP
#define UTILS_HPP

#include "circle_object.hpp"
#include "params.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

class CircleObject;

// vector math functions
float dot(sf::Vector2f &v1, sf::Vector2f &v2);
float magnitude_squared(sf::Vector2f &v);

// kinematics functions
void apply_gravity(sf::Vector2f &position, sf::Vector2f &velocity, sf::CircleShape &shape, float deltaTime);
void collide(CircleObject &thisShape, CircleObject &otherShape);
bool detect_collisions(const sf::CircleShape &thisShape, const sf::CircleShape &otherShape);

#endif