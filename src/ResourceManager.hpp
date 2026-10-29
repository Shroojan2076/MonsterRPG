#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class ResourceManager {
private:
    sf::Texture worldTileset;
    sf::Texture playerTexture;
    sf::Texture playerRunTexture;
    sf::Texture npcProfTexture;
    sf::Texture npcNurseTexture;
    sf::Texture npcVillagerTexture;

    std::unordered_map<std::string, sf::Texture> monsterTextures;
    sf::Font font;

public:
    ResourceManager();

    const sf::Texture& getWorldTileset() const;
    const sf::Texture& getPlayerTexture() const;
    const sf::Texture& getPlayerRunTexture() const;
    const sf::Texture& getNpcProfTexture() const;
    const sf::Texture& getNpcNurseTexture() const;
    const sf::Texture& getNpcVillagerTexture() const;
    const sf::Texture& getMonsterTexture(const std::string& key) const;
    const sf::Font& getFont() const;
};