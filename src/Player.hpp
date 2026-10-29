#pragma once

#include "Character.hpp"
#include "Item.hpp"
#include "Monster.hpp"
#include <vector>
#include <memory>
#include <functional>

class Player : public Character {
private:
    const sf::Texture& walkTexture;
    const sf::Texture& runTexture;
    bool isRunning;

    std::vector<std::shared_ptr<Monster>> party;
    Inventory inventory;

    bool hasStarterMonster;
    bool defeatedBoss;

    float turnCooldownTimer;
    Direction lastPressedDirection;

    std::function<void(sf::Vector2i)> onStepCompleted;
    std::function<bool(int, int)> collisionCheck;

    void handleInput(const TileMap& tileMap);

public:
    Player(int gridX, int gridY, const sf::Texture& walkTex, const sf::Texture& runTex);

    void update(float deltaTime, const TileMap& tileMap) override;

    sf::Vector2i getFrontTile() const;

    // Party and Inventory Management (Encapsulation)
    void addMonster(const std::shared_ptr<Monster>& monster);
    std::vector<std::shared_ptr<Monster>>& getParty();
    const std::vector<std::shared_ptr<Monster>>& getParty() const;
    std::shared_ptr<Monster> getFirstAliveMonster();
    void healAllMonsters();

    Inventory& getInventory();
    const Inventory& getInventory() const;

    bool hasStarter() const;
    void setHasStarter(bool val);

    bool isBossDefeated() const;
    void setBossDefeated(bool val);

    void setOnStepCompleted(std::function<void(sf::Vector2i)> callback);
    void setCollisionCallback(std::function<bool(int, int)> callback);
    bool getIsRunning() const { return isRunning; }
};