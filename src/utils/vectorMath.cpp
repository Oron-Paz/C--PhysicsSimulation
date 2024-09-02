#include "vectorMath.h"
#include <iostream>
#include <cmath>


float dot(sf::Vector2f& v1, sf::Vector2f& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

float magnitude_squared(sf::Vector2f& v) {
    return v.x * v.x + v.y * v.y;
}