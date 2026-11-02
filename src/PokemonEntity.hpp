#pragma once

#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <functional>

class TileMap;
class Player;
class ResourceManager;

class PokemonEntity : public Entity {
protected:
    std::string name;
    std::string speciesKey;
    const sf::Texture* texture;
    sf::Sprite sprite;
    bool facingLeft;
    float idleTimer;
    bool isWild;
    bool defeatedOrCaught;
    std::vector<std::string> dialogueLines;
    std::function<void(const std::string&, const std::vector<std::string>&, std::function<void()>)> dialogueTrigger;
    std::function<void()> battleTrigger;
    std::function<void(Player&)> customInteract;

    void updateSpriteOrigin();
    void triggerDialogue(const std::string& speaker, const std::vector<std::string>& lines, std::function<void()> onDone = nullptr) {
        if (dialogueTrigger) {
            dialogueTrigger(speaker, lines, std::move(onDone));
        }
    }

public:
    PokemonEntity(int gridX, int gridY, const sf::Texture& tex, std::string name, std::string speciesKey, bool isWild = false);

    void update(float deltaTime, const TileMap& tileMap) override;
    void draw(sf::RenderTarget& window) override;
    void onInteract(Player& player) override;

    bool isSolid() const override { return !defeatedOrCaught; }
    bool isInteractive() const override { return !defeatedOrCaught; }

    void setDialogue(std::vector<std::string> lines) { dialogueLines = std::move(lines); }
    void setDialogueTrigger(std::function<void(const std::string&, const std::vector<std::string>&, std::function<void()>)> trigger) {
        dialogueTrigger = std::move(trigger);
    }
    void setBattleTrigger(std::function<void()> trigger) { battleTrigger = std::move(trigger); }
    void setCustomInteract(std::function<void(Player&)> cb) { customInteract = std::move(cb); }

    void setDefeatedOrCaught(bool val) { defeatedOrCaught = val; }
    bool isDefeatedOrCaught() const { return defeatedOrCaught; }
    const std::string& getName() const { return name; }
    const std::string& getSpeciesKey() const { return speciesKey; }

    void setTexture(const sf::Texture& newTex);
    void turnTowards(const sf::Vector2i& targetPos);
};

// Follower Partner Pokémon walking behind the player
class FollowerPokemon : public PokemonEntity {
private:
    const ResourceManager& resources;
    sf::Vector2i targetGridPos;
    sf::Vector2f moveStartWorldPos;
    float moveProgress;
    bool moving;
    bool active;
    float speed;

public:
    FollowerPokemon(int gridX, int gridY, const ResourceManager& res);

    void syncWithPlayer(const Player& player);
    void onPlayerStep(sf::Vector2i prevTile, Direction playerFacing);
    void teleport(int x, int y);

    void update(float deltaTime, const TileMap& tileMap) override;
    void draw(sf::RenderTarget& window) override;
    void onInteract(Player& player) override;

    bool isSolid() const override { return false; } // Can't block player
    bool isInteractive() const override { return active; }
    bool isActive() const { return active; }
};
