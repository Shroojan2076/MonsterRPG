#include "WorldObject.hpp"
#include "Player.hpp"

// Signpost
Signpost::Signpost(int gridX, int gridY, std::string signName, std::vector<std::string> text)
    : WorldObject(gridX, gridY, std::move(signName)), message(std::move(text)) {}

void Signpost::update(float /*deltaTime*/, const TileMap& /*tileMap*/) {}
void Signpost::draw(sf::RenderTarget& /*window*/) {
    // Rendered via TileMap tile 17
}

void Signpost::onInteract(Player& /*player*/) {
    if (dialogueTrigger) {
        dialogueTrigger(name, message);
    }
}

// ItemBall
ItemBall::ItemBall(int gridX, int gridY, const sf::Texture& tilesetTexture)
    : WorldObject(gridX, gridY, "Item Ball"), collected(false), sprite(tilesetTexture) {
    // Tile 18 is row 2, col 2 in world_tileset.png
    sprite.setTextureRect(sf::IntRect({2 * 32, 2 * 32}, {32, 32}));
    sprite.setScale({0.5f, 0.5f});
    sprite.setPosition({static_cast<float>(gridX * 16), static_cast<float>(gridY * 16)});
}

void ItemBall::update(float /*deltaTime*/, const TileMap& /*tileMap*/) {}

void ItemBall::draw(sf::RenderTarget& window) {
    if (!collected) {
        window.draw(sprite);
    }
}

void ItemBall::onInteract(Player& player) {
    if (collected) return;
    collected = true;

    // Award items
    player.getInventory().addItem(std::make_shared<SuperPotionItem>(50), 2);
    player.getInventory().addItem(std::make_shared<CaptureBallItem>(1.2f), 3);

    if (dialogueTrigger) {
        std::vector<std::string> lines = {
            "You opened the mysterious item sphere!",
            "Obtained 2x Super Potions and 3x Capture Balls!",
            "Items have been tucked into your Bag."
        };
        dialogueTrigger(name, lines);
    }
}
