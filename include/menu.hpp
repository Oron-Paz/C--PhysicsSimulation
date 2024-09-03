#ifndef MENU_HPP
#define MENU_HPP

#include "utils.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Menu
{
  public:
    Menu();
    ~Menu();
    void draw(sf::RenderWindow &window);
    void moveUp();
    void moveDown();
    int getSelectedItemIndex();

  private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> options;
};

#endif