#include "../include/menu.hpp"

Menu::Menu()
{
    if (!font.loadFromFile("./assets/fonts/arial.ttf"))
    {
        std::cerr << "Error loading font" << std::endl;
    }

    options.resize(MAX_OPTIONS);
    selectedItemIndex = 0;

    title.setFont(font);
    title.setString("Main Menu");
    title.setCharacterSize(24);
    title.setFillColor(sf::Color::White);
    title.setPosition(sf::Vector2f(25, 25));

    for (int i = 0; i < MAX_OPTIONS; ++i)
    {
        options[i].setFont(font);
        options[i].setCharacterSize(20);
        options[i].setFillColor(sf::Color::White);
        options[i].setPosition(sf::Vector2f(50, 100 + 50 * i));
    }

    options[0].setString("Start Simulation");
    options[1].setString("Choose number of circles and start simulation");
    options[2].setString("Exit");

    options[0].setFillColor(sf::Color::Yellow);
}

Menu::~Menu()
{
    // Destructor
}

void Menu::draw(sf::RenderWindow &window)
{
    window.draw(title);
    for(int i = 0; i < MAX_OPTIONS; ++i)
    {
        window.draw(options[i]);
    }
}

void Menu::moveUp()
{
    if(selectedItemIndex - 1 >= 0)
    {
        options[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        options[selectedItemIndex].setFillColor(sf::Color::Yellow);
    }
}

void Menu::moveDown()
{
    if(selectedItemIndex + 1 < MAX_OPTIONS)
    {
        options[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        options[selectedItemIndex].setFillColor(sf::Color::Yellow);
    }
}

int Menu::getSelectedItemIndex()
{
    return selectedItemIndex;
}