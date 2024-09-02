#ifndef VECTOR_MATH_H
#define VECTOR_MATH_H

#include <SFML/Graphics.hpp>
#include "CircleObject.h"
#include <iostream>
#include <cmath>

float dot(sf::Vector2f& v1, sf::Vector2f& v2);
float magnitude_squared(sf::Vector2f& v);

#endif // VECTOR_MATH_H
