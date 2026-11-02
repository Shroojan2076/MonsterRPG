#pragma once

#include "GameState.hpp"
#include "TileMap.hpp"
#include "Player.hpp"
#include "Entity.hpp"
#include "PokemonEntity.hpp"
#include <vector>
#include <memory>

class ResourceManager;

class OverworldState : public GameState {
public:
    enum class TransitionState {
        None,
        FadingOut,
        FadingIn
    };

private:
    const ResourceManager& resources;
    TileMap tileMap;
    Player player;
    FollowerPokemon follower;

    // Polymorphic collections of Entities per map
    std::vector<std::unique_ptr<Entity>> overworldEntities;
    std::vector<std::unique_ptr<Entity>> oakLabEntities;
    std::vector<std::unique_ptr<Entity>> pokemonCenterEntities;
    std::vector<std::unique_ptr<Entity>>* activeEntities;

    // Warp transition states
    TransitionState transitionState;
    float transitionAlpha;
    static constexpr float TRANSITION_SPEED = 650.0f; // Smooth fade transition
    MapId pendingMapId;
    sf::Vector2i pendingTargetPos;
    Direction pendingTargetDir;

    sf::View gameView;
    static constexpr float VIEW_WIDTH = 240.0f;
    static constexpr float VIEW_HEIGHT = 160.0f;

    void initializeEntities();
    void handleInteraction();
    void checkWildEncounter(sf::Vector2i playerGridPos);
    bool checkWarpTrigger(sf::Vector2i playerGridPos);
    void startWarp(MapId targetMap, sf::Vector2i targetPos, Direction targetDir);
    void executeWarp(MapId targetMap, sf::Vector2i targetPos, Direction targetDir);

public:
    OverworldState(StateManager& manager, const ResourceManager& res);

    void handleInput(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderTarget& target) override;
};
