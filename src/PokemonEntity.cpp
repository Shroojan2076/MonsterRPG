#include "PokemonEntity.hpp"
#include "Player.hpp"
#include "ResourceManager.hpp"
#include <cmath>

PokemonEntity::PokemonEntity(int gridX, int gridY, const sf::Texture& tex, std::string name, std::string speciesKey, bool isWild)
    : Entity(gridX, gridY),
      name(std::move(name)),
      speciesKey(std::move(speciesKey)),
      texture(&tex),
      sprite(tex),
      facingLeft(false),
      idleTimer(0.0f),
      isWild(isWild),
      defeatedOrCaught(false) {
    updateSpriteOrigin();
}

void PokemonEntity::updateSpriteOrigin() {
    if (!texture) return;
    auto size = texture->getSize();
    float w = static_cast<float>(size.x);
    float h = static_cast<float>(size.y);

    sprite.setTexture(*texture, true);
    sprite.setOrigin({w / 2.0f, h});
    
    // Scale slightly if large 32x32 sprite, or 1:1 for 16x16
    float scale = (w > 20.0f || h > 20.0f) ? 0.9f : 1.0f;
    sprite.setScale({facingLeft ? -scale : scale, scale});
    sprite.setPosition({worldPosition.x + 8.0f, worldPosition.y + 16.0f});
}

void PokemonEntity::setTexture(const sf::Texture& newTex) {
    texture = &newTex;
    updateSpriteOrigin();
}

void PokemonEntity::turnTowards(const sf::Vector2i& targetPos) {
    if (targetPos.x < gridPosition.x) {
        facingLeft = true;
    } else if (targetPos.x > gridPosition.x) {
        facingLeft = false;
    }
    if (texture) {
        float scale = (texture->getSize().x > 20 || texture->getSize().y > 20) ? 0.9f : 1.0f;
        sprite.setScale({facingLeft ? -scale : scale, scale});
    }
}

void PokemonEntity::update(float deltaTime, const TileMap& /*tileMap*/) {
    if (defeatedOrCaught) return;

    idleTimer += deltaTime;
    // Gentle breathing / hopping effect
    float hop = std::abs(std::sin(idleTimer * 3.5f)) * 1.5f;
    sprite.setPosition({worldPosition.x + 8.0f, worldPosition.y + 16.0f - hop});
}

void PokemonEntity::draw(sf::RenderTarget& window) {
    if (defeatedOrCaught) return;
    window.draw(sprite);
}

void PokemonEntity::onInteract(Player& player) {
    if (defeatedOrCaught) return;
    turnTowards(player.getGridPosition());

    if (customInteract) {
        customInteract(player);
        return;
    }

    if (!dialogueLines.empty()) {
        triggerDialogue(name, dialogueLines, battleTrigger);
    } else if (battleTrigger) {
        battleTrigger();
    }
}

// FollowerPokemon Implementation
FollowerPokemon::FollowerPokemon(int gridX, int gridY, const ResourceManager& res)
    : PokemonEntity(gridX, gridY, res.getPokemonOverworldTexture("025_PIKACHU"), "Partner", "025_PIKACHU", false),
      resources(res),
      targetGridPos({gridX, gridY}),
      moveStartWorldPos({static_cast<float>(gridX * 16), static_cast<float>(gridY * 16)}),
      moveProgress(0.0f),
      moving(false),
      active(false),
      speed(55.0f) {}

void FollowerPokemon::syncWithPlayer(const Player& player) {
    if (!player.hasStarter()) {
        active = false;
        return;
    }
    auto lead = const_cast<Player&>(player).getFirstAliveMonster();
    if (!lead) {
        active = false;
        return;
    }

    active = true;
    if (lead->getTextureKey() != speciesKey) {
        speciesKey = lead->getTextureKey();
        name = lead->getName();
        setTexture(resources.getPokemonOverworldTexture(speciesKey));
    }
}

void FollowerPokemon::onPlayerStep(sf::Vector2i prevTile, Direction /*playerFacing*/) {
    if (!active) return;
    if (gridPosition == prevTile) return;

    targetGridPos = prevTile;
    moveStartWorldPos = worldPosition;
    moveProgress = 0.0f;
    moving = true;

    // Follower turns towards its movement direction
    if (targetGridPos.x < gridPosition.x) {
        facingLeft = true;
    } else if (targetGridPos.x > gridPosition.x) {
        facingLeft = false;
    }
    if (texture) {
        float scale = (texture->getSize().x > 20 || texture->getSize().y > 20) ? 0.9f : 1.0f;
        sprite.setScale({facingLeft ? -scale : scale, scale});
    }
}

void FollowerPokemon::teleport(int x, int y) {
    gridPosition = {x, y};
    worldPosition = {static_cast<float>(x * 16), static_cast<float>(y * 16)};
    targetGridPos = gridPosition;
    moveStartWorldPos = worldPosition;
    moving = false;
    moveProgress = 0.0f;
    sprite.setPosition({worldPosition.x + 8.0f, worldPosition.y + 16.0f});
}

void FollowerPokemon::update(float deltaTime, const TileMap& tileMap) {
    if (!active) return;

    if (moving) {
        moveProgress += speed * deltaTime;
        if (moveProgress >= 16.0f) {
            moveProgress = 16.0f;
            moving = false;
            gridPosition = targetGridPos;
            worldPosition = {static_cast<float>(gridPosition.x * 16), static_cast<float>(gridPosition.y * 16)};
        } else {
            float t = moveProgress / 16.0f;
            sf::Vector2f targetWorld({static_cast<float>(targetGridPos.x * 16), static_cast<float>(targetGridPos.y * 16)});
            worldPosition = moveStartWorldPos + (targetWorld - moveStartWorldPos) * t;
        }
    }

    PokemonEntity::update(deltaTime, tileMap);
}

void FollowerPokemon::draw(sf::RenderTarget& window) {
    if (!active) return;
    PokemonEntity::draw(window);
}

void FollowerPokemon::onInteract(Player& player) {
    if (!active) return;
    turnTowards(player.getGridPosition());

    auto lead = player.getFirstAliveMonster();
    std::string mood;
    if (lead) {
        if (lead->getCurrentHp() == lead->getMaxHp()) {
            mood = "It is bursting with vibrant energy and ready for anything!";
        } else if (lead->getCurrentHp() > lead->getMaxHp() / 2) {
            mood = "It gives you a determined nod and nudges your knee.";
        } else {
            mood = "It looks slightly exhausted, but stays bravely by your side.";
        }
    }

    std::vector<std::string> lines = {
        name + ": '" + name + "!'",
        name + " looks up at you with deep affection and trust.",
        mood
    };

    if (dialogueTrigger) {
        triggerDialogue(name + " (Partner)", lines);
    }
}
