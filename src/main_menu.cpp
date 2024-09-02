#include "../include/main_menu.hpp"

MainMenu::MainMenu()
{
    if (!font.loadFromFile("./assets/fonts/arial.ttf"))
    {
        std::cerr << "Error loading font" << std::endl;
    }

    selectedOption = 0;

    title.setFont(font);
    title.setString("Main Menu");
    title.setCharacterSize(24);
    title.setFillColor(sf::Color::White);
    title.setPosition(10, 10);

    startSimulation.setFont(font);
    startSimulation.setString("Start Simulation");
    startSimulation.setCharacterSize(24);
    startSimulation.setFillColor(sf::Color::White);
    startSimulation.setPosition(10, 40);

    exit.setFont(font);
    exit.setString("Exit");
    exit.setCharacterSize(24);
    exit.setFillColor(sf::Color::White);
    exit.setPosition(10, 70);
}

MainMenu::~MainMenu()
{
    // Destructor
}

void MainMenu::draw(sf::RenderWindow &window)
{
    window.draw(title);
    window.draw(startSimulation);
    window.draw(exit);
}

void MainMenu::update(float deltaTime)
{
    deltaTime = deltaTime;
}

void MainMenu::handleInput(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Up)
            {
                selectedOption = (selectedOption - 1 + 2) % 2;
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                selectedOption = (selectedOption + 1) % 2;
            }
            else if (event.key.code == sf::Keyboard::Enter)
            {
                if (selectedOption == 0)
                {
                    setSimulationState(SimulationState::START);
                }
                else if (selectedOption == 1)
                {
                    setSimulationState(SimulationState::EXIT);
                }
            }
        }
    }
}

void MainMenu::setSimulationState(SimulationState state)
{
    simulationState = state;
}

SimulationState MainMenu::getSimulationState()
{
    return simulationState;
}