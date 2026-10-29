#include "ResourceManager.hpp"
#include <stdexcept>

ResourceManager::ResourceManager() {
    if (!worldTileset.loadFromFile("assets/world_tileset.png")) {
        throw std::runtime_error("Failed to load world tileset texture.");
    }
    if (!playerTexture.loadFromFile("assets/HGSS_boy.png")) {
        throw std::runtime_error("Failed to load player texture.");
    }
    if (!playerRunTexture.loadFromFile("assets/HGSS_boy_run.png")) {
        throw std::runtime_error("Failed to load player run texture.");
    }
    if (!npcProfTexture.loadFromFile("assets/npc_prof.png")) {
        throw std::runtime_error("Failed to load professor NPC texture.");
    }
    if (!npcNurseTexture.loadFromFile("assets/npc_nurse.png")) {
        throw std::runtime_error("Failed to load nurse NPC texture.");
    }
    if (!npcVillagerTexture.loadFromFile("assets/npc_villager.png")) {
        throw std::runtime_error("Failed to load villager NPC texture.");
    }

    // Monster textures
    const std::vector<std::string> monsterNames = {
        "grassling", "pyropup", "aquafox", "voltmouse", "sylvanguard"
    };

    for (const auto& name : monsterNames) {
        sf::Texture tex;
        if (!tex.loadFromFile("assets/monsters/" + name + ".png")) {
            throw std::runtime_error("Failed to load monster texture: " + name);
        }
        monsterTextures[name] = tex;
    }

    if (!font.openFromFile("assets/font.ttf")) {
        throw std::runtime_error("Failed to open font file.");
    }
}

const sf::Texture& ResourceManager::getWorldTileset() const { return worldTileset; }
const sf::Texture& ResourceManager::getPlayerTexture() const { return playerTexture; }
const sf::Texture& ResourceManager::getPlayerRunTexture() const { return playerRunTexture; }
const sf::Texture& ResourceManager::getNpcProfTexture() const { return npcProfTexture; }
const sf::Texture& ResourceManager::getNpcNurseTexture() const { return npcNurseTexture; }
const sf::Texture& ResourceManager::getNpcVillagerTexture() const { return npcVillagerTexture; }

const sf::Texture& ResourceManager::getMonsterTexture(const std::string& key) const {
    auto it = monsterTextures.find(key);
    if (it != monsterTextures.end()) {
        return it->second;
    }
    // Fallback to grassling if not found
    return monsterTextures.at("grassling");
}

const sf::Font& ResourceManager::getFont() const { return font; }