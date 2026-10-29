#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class StateManager;

// Abstract Base Class for Game States (OOP State Pattern)
class GameState {
protected:
    StateManager& stateManager;

public:
    explicit GameState(StateManager& manager) : stateManager(manager) {}
    virtual ~GameState() = default;

    virtual void handleInput(const sf::Event& event) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderTarget& target) = 0;

    // If true, the state manager renders the state underneath it before rendering this state
    virtual bool isOverlay() const { return false; }
};
