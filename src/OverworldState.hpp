#pragma once

#include "GameState.hpp"
#include "TileMap.hpp"
#include "Player.hpp"
#include "Entity.hpp"
#include <vector>
#include <memory>

class ResourceManager;

class OverworldState : public GameState {
private:
    const ResourceManager& resources;
    TileMap tileMap;
    Player player;
    std::vector<std::unique_ptr<Entity>> entities; // Polymorphic collection of Entities

    sf::View gameView;
    static constexpr float VIEW_WIDTH = 240.0f;
    static constexpr float VIEW_HEIGHT = 160.0f;

    void initializeEntities();
    void handleInteraction();
    void checkWildEncounter(sf::Vector2i playerGridPos);

public:
    OverworldState(StateManager& manager, const ResourceManager& res);

    void handleInput(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderTarget& target) override;
};
