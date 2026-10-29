#pragma once

#include "Entity.hpp"
#include <string>
#include <vector>
#include <functional>

// Abstract Base Class for stationary interactable world props
class WorldObject : public Entity {
protected:
    std::string name;
    std::function<void(const std::string&, const std::vector<std::string>&)> dialogueTrigger;

public:
    WorldObject(int gridX, int gridY, std::string name)
        : Entity(gridX, gridY), name(std::move(name)) {}

    void setDialogueTrigger(std::function<void(const std::string&, const std::vector<std::string>&)> trigger) {
        dialogueTrigger = std::move(trigger);
    }

    bool isInteractive() const override { return true; }
};

// Derived 1: Signpost
class Signpost : public WorldObject {
private:
    std::vector<std::string> message;

public:
    Signpost(int gridX, int gridY, std::string signName, std::vector<std::string> text);

    void update(float deltaTime, const TileMap& tileMap) override;
    void draw(sf::RenderTarget& window) override;
    void onInteract(Player& player) override;
    bool isSolid() const override { return true; }
};

// Derived 2: ItemBall / Treasure Chest
class ItemBall : public WorldObject {
private:
    bool collected;
    sf::Sprite sprite;

public:
    ItemBall(int gridX, int gridY, const sf::Texture& tilesetTexture);

    void update(float deltaTime, const TileMap& tileMap) override;
    void draw(sf::RenderTarget& window) override;
    void onInteract(Player& player) override;
    bool isSolid() const override { return !collected; }
    bool isCollected() const { return collected; }
};
