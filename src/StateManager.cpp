#include "StateManager.hpp"
#include "GameState.hpp"

StateManager::StateManager() = default;
StateManager::~StateManager() = default;

void StateManager::processPendingChanges() {
    if (popRequested && !states.empty()) {
        states.pop_back();
        popRequested = false;
    }
    if (pendingPush) {
        states.push_back(std::move(pendingPush));
        pendingPush = nullptr;
    }
}

void StateManager::pushState(std::unique_ptr<GameState> state) {
    if (states.empty()) {
        states.push_back(std::move(state));
    } else {
        pendingPush = std::move(state);
    }
}

void StateManager::popState() {
    popRequested = true;
}

void StateManager::changeState(std::unique_ptr<GameState> state) {
    states.clear();
    states.push_back(std::move(state));
    popRequested = false;
    pendingPush = nullptr;
}

void StateManager::handleInput(const sf::Event& event) {
    processPendingChanges();
    if (!states.empty()) {
        states.back()->handleInput(event);
    }
}

void StateManager::update(float deltaTime) {
    processPendingChanges();
    if (!states.empty()) {
        states.back()->update(deltaTime);
    }
}

void StateManager::render(sf::RenderTarget& target) {
    if (states.empty()) return;

    // If top state is overlay, render the state below it first
    if (states.back()->isOverlay() && states.size() >= 2) {
        states[states.size() - 2]->render(target);
    }

    states.back()->render(target);
}

bool StateManager::isEmpty() const {
    return states.empty() && pendingPush == nullptr;
}

GameState* StateManager::getCurrentState() {
    return states.empty() ? nullptr : states.back().get();
}
