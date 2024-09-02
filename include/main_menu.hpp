#include <SFML/Graphics.hpp>
#include <iostream>
#include "utils.hpp"

class MainMenu
{
public:
    MainMenu();
    ~MainMenu();
    void draw(sf::RenderWindow &window);
    void update(float deltaTime);
    void handleInput(sf::RenderWindow &window);
    void setSimulationState(SimulationState state);
    SimulationState getSimulationState();

private:
    SimulationState simulationState;
    sf::Font font;
    sf::Text title;
    sf::Text startSimulation;
    sf::Text exit;
    short int selectedOption;
};