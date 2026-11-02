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

    // Caches for Pokémon sprites
    mutable std::unordered_map<std::string, sf::Texture> pokemonFrontTextures;
    mutable std::unordered_map<std::string, sf::Texture> pokemonBackTextures;
    mutable std::unordered_map<std::string, sf::Texture> pokemonOverworldTextures;
    mutable std::unordered_map<std::string, sf::Texture> monsterTextures; // legacy fallback

    // Mappings of normalized keys to actual filenames
    std::unordered_map<std::string, std::string> frontFilenameMap;
    std::unordered_map<std::string, std::string> overworldFilenameMap;

    sf::Font font;

    void initializeFilenameMaps();
    std::string resolveFrontFilename(const std::string& key) const;
    std::string resolveOverworldFilename(const std::string& key) const;

public:
    ResourceManager();

    const sf::Texture& getWorldTileset() const;
    const sf::Texture& getPlayerTexture() const;
    const sf::Texture& getPlayerRunTexture() const;
    const sf::Texture& getNpcProfTexture() const;
    const sf::Texture& getNpcNurseTexture() const;
    const sf::Texture& getNpcVillagerTexture() const;
    const sf::Font& getFont() const;

    // Pokémon battle sprites (64x64)
    const sf::Texture& getPokemonFrontTexture(const std::string& key) const;
    const sf::Texture& getPokemonBackTexture(const std::string& key) const;

    // Pokémon overworld sprites (from assets/overworld)
    const sf::Texture& getPokemonOverworldTexture(const std::string& key) const;

    // Legacy monster texture getter (delegates to getPokemonFrontTexture)
    const sf::Texture& getMonsterTexture(const std::string& key) const;
};
