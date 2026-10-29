#pragma once

#include <SFML/Graphics.hpp>
#include "Common.hpp"

class TileMap;
class Player;

// Abstract Base Class for all world entities (OOP Abstraction & Polymorphism)
class Entity {
protected:
    sf::Vector2i gridPosition;
    sf::Vector2f worldPosition;

public:
    Entity(int gridX, int gridY)
        : gridPosition({gridX, gridY}),
          worldPosition({static_cast<float>(gridX * 16), static_cast<float>(gridY * 16)}) {}

    virtual ~Entity() = default;

    // Pure virtual methods ensuring all entities define update and render behavior
    virtual void update(float deltaTime, const TileMap& tileMap) = 0;
    virtual void draw(sf::RenderTarget& window) = 0;

    // Virtual interaction hook
    virtual void onInteract(Player& /*player*/) {}
    virtual bool isSolid() const { return true; }
    virtual bool isInteractive() const { return false; }

    sf::Vector2i getGridPosition() const { return gridPosition; }
    sf::Vector2f getWorldPosition() const { return worldPosition; }
    void setGridPosition(int x, int y) {
        gridPosition = {x, y};
        worldPosition = {static_cast<float>(x * 16), static_cast<float>(y * 16)};
    }
};
