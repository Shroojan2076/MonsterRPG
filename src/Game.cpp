#include "Game.hpp"
#include "OverworldState.hpp"

Game::Game()
    : window(sf::VideoMode({960, 640}), "Monster RPG - Pokemon OOP Edition"),
      resourceManager() {
    window.setFramerateLimit(60);
    // Push the initial Overworld state
    stateManager.pushState(std::make_unique<OverworldState>(stateManager, resourceManager));
}

void Game::run() {
    while (window.isOpen() && !stateManager.isEmpty()) {
        processEvents();
        float deltaTime = clock.restart().asSeconds();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
            return;
        }
        stateManager.handleInput(*event);
    }
}

void Game::update(float deltaTime) {
    stateManager.update(deltaTime);
}

void Game::render() {
    window.clear(sf::Color::Black);
    stateManager.render(window);
    window.display();
}