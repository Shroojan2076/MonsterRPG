#pragma once

#include <SFML/Graphics.hpp>
#include "ResourceManager.hpp"
#include "StateManager.hpp"

class Game {
private:
    sf::RenderWindow window;
    sf::Clock clock;

    ResourceManager resourceManager;
    StateManager stateManager;

    void processEvents();
    void update(float deltaTime);
    void render();

public:
    Game();
    void run();
};