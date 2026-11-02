#include "ResourceManager.hpp"
#include <stdexcept>
#include <filesystem>
#include <algorithm>
#include <cctype>

namespace {
    std::string toLower(std::string s) {
        std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
            return static_cast<char>(std::tolower(c));
        });
        return s;
    }
}

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
    if (!font.openFromFile("assets/font.ttf")) {
        throw std::runtime_error("Failed to open font file.");
    }

    initializeFilenameMaps();
}

void ResourceManager::initializeFilenameMaps() {
    // 1. Index all front/back Pokémon files
    namespace fs = std::filesystem;
    if (fs::exists("assets/pokemon/front")) {
        for (const auto& entry : fs::directory_iterator("assets/pokemon/front")) {
            if (!entry.is_regular_file()) continue;
            std::string filename = entry.path().filename().string();
            std::string stem = entry.path().stem().string();

            // Store full stem
            frontFilenameMap[toLower(stem)] = filename;
            frontFilenameMap[stem] = filename;

            // If format is like "001_BULBASAUR"
            auto underscorePos = stem.find('_');
            if (underscorePos != std::string::npos) {
                std::string numPart = stem.substr(0, underscorePos);
                std::string namePart = stem.substr(underscorePos + 1);

                frontFilenameMap[toLower(numPart)] = filename;
                frontFilenameMap[toLower(namePart)] = filename;
                frontFilenameMap[namePart] = filename;

                // Also strip leading zeroes for number
                size_t firstNonZero = numPart.find_first_not_of('0');
                if (firstNonZero != std::string::npos) {
                    frontFilenameMap[numPart.substr(firstNonZero)] = filename;
                }
            }
        }
    }

    // Legacy / game alias mappings
    frontFilenameMap["pyropup"] = "004_CHARMANDER.png";
    frontFilenameMap["aquafox"] = "007_SQUIRTLE.png";
    frontFilenameMap["grassling"] = "001_BULBASAUR.png";
    frontFilenameMap["voltmouse"] = "025_PIKACHU.png";
    frontFilenameMap["sylvanguard"] = "150_MEWTWO.png";

    // 2. Overworld Pokémon sprite mappings
    auto registerOw = [this](const std::vector<std::string>& aliases, const std::string& owFile) {
        for (const auto& a : aliases) {
            overworldFilenameMap[toLower(a)] = owFile;
        }
    };

    registerOw({"025", "25", "pikachu", "025_pikachu", "voltmouse"}, "ow_143.png");
    registerOw({"004", "4", "charmander", "004_charmander", "pyropup"}, "ow_149.png");
    registerOw({"007", "7", "squirtle", "007_squirtle", "aquafox"}, "ow_133.png");
    registerOw({"001", "1", "bulbasaur", "001_bulbasaur", "grassling"}, "ow_134.png");
    registerOw({"150", "mewtwo", "150_mewtwo", "sylvanguard"}, "ow_131.png");
    registerOw({"143", "snorlax", "143_snorlax"}, "ow_127.png");
    registerOw({"131", "lapras", "131_lapras"}, "ow_128.png");
    registerOw({"144", "articuno", "144_articuno"}, "ow_129.png");
    registerOw({"146", "moltres", "146_moltres"}, "ow_130.png");
    registerOw({"145", "zapdos", "145_zapdos"}, "ow_132.png");
    registerOw({"133", "eevee", "133_eevee"}, "ow_135.png");
    registerOw({"037", "37", "vulpix", "037_vulpix"}, "ow_136.png");
    registerOw({"100", "voltorb", "100_voltorb"}, "ow_137.png");
    registerOw({"249", "lugia", "249_lugia"}, "ow_138.png");
    registerOw({"250", "ho_oh", "ho-oh", "250_ho_oh"}, "ow_139.png");
    registerOw({"060", "60", "poliwag", "060_poliwag"}, "ow_140.png");
    registerOw({"094", "94", "gengar", "094_gengar"}, "ow_141.png");
    registerOw({"024", "24", "arbok", "024_arbok"}, "ow_142.png");
    registerOw({"066", "66", "machop", "066_machop"}, "ow_144.png");
    registerOw({"052", "52", "meowth", "052_meowth"}, "ow_145.png");
    registerOw({"035", "35", "clefairy", "035_clefairy"}, "ow_146.png");
    registerOw({"054", "54", "psyduck", "054_psyduck"}, "ow_147.png");
    registerOw({"039", "39", "jigglypuff", "039_jigglypuff"}, "ow_148.png");
    registerOw({"016", "16", "pidgey", "016_pidgey"}, "ow_149.png");

    // Also register direct "ow_000" to "ow_149"
    for (int i = 0; i < 150; ++i) {
        char buf[16];
        snprintf(buf, sizeof(buf), "ow_%03d", i);
        overworldFilenameMap[buf] = std::string(buf) + ".png";
        overworldFilenameMap[std::string(buf) + ".png"] = std::string(buf) + ".png";
    }
}

std::string ResourceManager::resolveFrontFilename(const std::string& key) const {
    std::string lk = toLower(key);
    auto it = frontFilenameMap.find(lk);
    if (it != frontFilenameMap.end()) {
        return it->second;
    }
    // Check if ends with .png
    if (lk.size() > 4 && lk.substr(lk.size() - 4) == ".png") {
        return key;
    }
    return "001_BULBASAUR.png"; // safe fallback
}

std::string ResourceManager::resolveOverworldFilename(const std::string& key) const {
    std::string lk = toLower(key);
    auto it = overworldFilenameMap.find(lk);
    if (it != overworldFilenameMap.end()) {
        return it->second;
    }
    // Check if filename directly matches
    if (lk.rfind("ow_", 0) == 0) {
        if (lk.size() > 4 && lk.substr(lk.size() - 4) == ".png") return lk;
        return lk + ".png";
    }
    return "ow_143.png"; // default Pikachu
}

const sf::Texture& ResourceManager::getWorldTileset() const { return worldTileset; }
const sf::Texture& ResourceManager::getPlayerTexture() const { return playerTexture; }
const sf::Texture& ResourceManager::getPlayerRunTexture() const { return playerRunTexture; }
const sf::Texture& ResourceManager::getNpcProfTexture() const { return npcProfTexture; }
const sf::Texture& ResourceManager::getNpcNurseTexture() const { return npcNurseTexture; }
const sf::Texture& ResourceManager::getNpcVillagerTexture() const { return npcVillagerTexture; }
const sf::Font& ResourceManager::getFont() const { return font; }

const sf::Texture& ResourceManager::getPokemonFrontTexture(const std::string& key) const {
    std::string filename = resolveFrontFilename(key);
    auto it = pokemonFrontTextures.find(filename);
    if (it != pokemonFrontTextures.end()) {
        return it->second;
    }

    sf::Texture tex;
    std::string path = "assets/pokemon/front/" + filename;
    if (!tex.loadFromFile(path)) {
        // Fallback to Bulbasaur
        path = "assets/pokemon/front/001_BULBASAUR.png";
        (void)tex.loadFromFile(path);
    }
    auto [insertedIt, _] = pokemonFrontTextures.emplace(filename, std::move(tex));
    return insertedIt->second;
}

const sf::Texture& ResourceManager::getPokemonBackTexture(const std::string& key) const {
    std::string filename = resolveFrontFilename(key); // back files share same names
    auto it = pokemonBackTextures.find(filename);
    if (it != pokemonBackTextures.end()) {
        return it->second;
    }

    sf::Texture tex;
    std::string path = "assets/pokemon/back/" + filename;
    if (!tex.loadFromFile(path)) {
        // Fallback to front or Bulbasaur
        path = "assets/pokemon/back/001_BULBASAUR.png";
        (void)tex.loadFromFile(path);
    }
    auto [insertedIt, _] = pokemonBackTextures.emplace(filename, std::move(tex));
    return insertedIt->second;
}

const sf::Texture& ResourceManager::getPokemonOverworldTexture(const std::string& key) const {
    std::string filename = resolveOverworldFilename(key);
    auto it = pokemonOverworldTextures.find(filename);
    if (it != pokemonOverworldTextures.end()) {
        return it->second;
    }

    sf::Texture tex;
    std::string path = "assets/overworld/" + filename;
    if (!tex.loadFromFile(path)) {
        path = "assets/overworld/ow_143.png"; // Fallback Pikachu
        (void)tex.loadFromFile(path);
    }
    auto [insertedIt, _] = pokemonOverworldTextures.emplace(filename, std::move(tex));
    return insertedIt->second;
}

const sf::Texture& ResourceManager::getMonsterTexture(const std::string& key) const {
    return getPokemonFrontTexture(key);
}
