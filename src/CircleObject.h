#ifndef CIRCLEOBJECT_H
#define CIRCLEOBJECT_H

#include <SFML/Graphics.hpp>
#include "kinematics/kinematics.h"

class CircleObject {

public:
    CircleObject(int radius, sf::Color color, sf::Vector2f position); // Constructor
    CircleObject(); // Default constructor
    void draw(sf::RenderWindow& window);  // Pass window by reference
    void update(float deltaTime);  // Update function to apply gravity);
    sf::CircleShape shape;
   

private:
    //int radius;
    sf::Color color;
    //sf::CircleShape shape;
    sf::Vector2f position;
    sf::Vector2f velocity;

};

#endif // CIRCLEOBJECT_H
