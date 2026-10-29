#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "GameState.hpp"

// State Manager (Composition & State Machine)
class StateManager {
private:
    std::vector<std::unique_ptr<GameState>> states;
    bool popRequested = false;
    std::unique_ptr<GameState> pendingPush = nullptr;

    void processPendingChanges();

public:
    StateManager();
    ~StateManager();

    void pushState(std::unique_ptr<GameState> state);
    void popState();
    void changeState(std::unique_ptr<GameState> state);

    void handleInput(const sf::Event& event);
    void update(float deltaTime);
    void render(sf::RenderTarget& target);

    bool isEmpty() const;
    GameState* getCurrentState();
};
