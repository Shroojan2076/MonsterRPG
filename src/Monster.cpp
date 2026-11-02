#include "Monster.hpp"
#include <algorithm>
#include <random>

// Move Implementation
Move::Move(std::string name, ElementType type, int power, int accuracy)
    : name(std::move(name)), type(type), power(power), accuracy(accuracy) {}

const std::string& Move::getName() const { return name; }
ElementType Move::getType() const { return type; }
int Move::getPower() const { return power; }
int Move::getAccuracy() const { return accuracy; }

std::string Move::getTypeName() const {
    switch (type) {
        case ElementType::Normal:   return "Normal";
        case ElementType::Fire:     return "Fire";
        case ElementType::Water:    return "Water";
        case ElementType::Grass:    return "Grass";
        case ElementType::Electric: return "Electric";
        default:                    return "Unknown";
    }
}

// Monster Implementation
Monster::Monster(std::string name, ElementType type, int level, int baseHp, int baseAtk, int baseDef, int baseSpd, std::string textureKey)
    : name(std::move(name)), type(type), level(level), textureKey(std::move(textureKey)) {
    maxHp = baseHp + (level * 3);
    currentHp = maxHp;
    attack = baseAtk + (level * 2);
    defense = baseDef + (level * 2);
    speed = baseSpd + (level * 2);
    exp = 0;
    expToNextLevel = level * 20;
}

void Monster::addMove(const Move& move) {
    if (moves.size() < 4) {
        moves.push_back(move);
    }
}

void Monster::recalculateStats() {
    int oldMax = maxHp;
    maxHp = 20 + (level * 4);
    attack = 10 + (level * 3);
    defense = 8 + (level * 2);
    speed = 9 + (level * 2);
    currentHp += (maxHp - oldMax); // retain proportional health
    expToNextLevel = level * 25;
}

float Monster::getTypeMultiplier(ElementType attackType, ElementType defenderType) {
    if (attackType == ElementType::Fire) {
        if (defenderType == ElementType::Grass) return 2.0f;
        if (defenderType == ElementType::Water) return 0.5f;
    } else if (attackType == ElementType::Water) {
        if (defenderType == ElementType::Fire) return 2.0f;
        if (defenderType == ElementType::Grass) return 0.5f;
    } else if (attackType == ElementType::Grass) {
        if (defenderType == ElementType::Water) return 2.0f;
        if (defenderType == ElementType::Fire) return 0.5f;
    } else if (attackType == ElementType::Electric) {
        if (defenderType == ElementType::Water) return 2.0f;
        if (defenderType == ElementType::Grass) return 0.5f;
    }
    return 1.0f;
}

int Monster::takeDamage(int movePower, ElementType moveType, const Monster& attacker, float& outMultiplier) {
    outMultiplier = getTypeMultiplier(moveType, type);
    float baseDmg = static_cast<float>(attacker.getAttack() * movePower) / std::max(1.0f, static_cast<float>(defense) * 1.5f);
    int damage = std::max(1, static_cast<int>(baseDmg * outMultiplier));
    currentHp = std::max(0, currentHp - damage);
    return damage;
}

void Monster::heal(int amount) {
    currentHp = std::min(maxHp, currentHp + amount);
}

void Monster::fullHeal() {
    currentHp = maxHp;
}

bool Monster::gainExp(int amount) {
    exp += amount;
    if (exp >= expToNextLevel) {
        exp -= expToNextLevel;
        level++;
        recalculateStats();
        return true;
    }
    return false;
}

bool Monster::isFainted() const {
    return currentHp <= 0;
}

const std::string& Monster::getName() const { return name; }
ElementType Monster::getType() const { return type; }
int Monster::getLevel() const { return level; }
int Monster::getCurrentHp() const { return currentHp; }
int Monster::getMaxHp() const { return maxHp; }
int Monster::getAttack() const { return attack; }
int Monster::getDefense() const { return defense; }
int Monster::getSpeed() const { return speed; }
int Monster::getExp() const { return exp; }
int Monster::getExpToNextLevel() const { return expToNextLevel; }
const std::string& Monster::getTextureKey() const { return textureKey; }
const std::vector<Move>& Monster::getMoves() const { return moves; }

std::string Monster::getTypeName() const {
    switch (type) {
        case ElementType::Normal:   return "Normal";
        case ElementType::Fire:     return "Fire";
        case ElementType::Water:    return "Water";
        case ElementType::Grass:    return "Grass";
        case ElementType::Electric: return "Electric";
        default:                    return "Unknown";
    }
}

std::shared_ptr<Monster> Monster::createStarterMonster(int choice) {
    if (choice == 1) { // Fire
        auto m = std::make_shared<Monster>("Charmander", ElementType::Fire, 5, 24, 14, 10, 12, "004_CHARMANDER");
        m->addMove(Move("Scratch", ElementType::Normal, 15, 95));
        m->addMove(Move("Ember", ElementType::Fire, 22, 90));
        return m;
    } else if (choice == 2) { // Water
        auto m = std::make_shared<Monster>("Squirtle", ElementType::Water, 5, 26, 12, 12, 11, "007_SQUIRTLE");
        m->addMove(Move("Tackle", ElementType::Normal, 15, 95));
        m->addMove(Move("Water Gun", ElementType::Water, 22, 90));
        return m;
    } else { // Grass
        auto m = std::make_shared<Monster>("Bulbasaur", ElementType::Grass, 5, 28, 11, 13, 10, "001_BULBASAUR");
        m->addMove(Move("Tackle", ElementType::Normal, 15, 95));
        m->addMove(Move("Vine Whip", ElementType::Grass, 22, 90));
        return m;
    }
}

std::shared_ptr<Monster> Monster::createSpecificWildMonster(const std::string& species, int level) {
    std::string key = species;
    std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

    if (key == "pikachu" || key == "025" || key == "025_pikachu") {
        auto m = std::make_shared<Monster>("Wild Pikachu", ElementType::Electric, level, 20, 14, 8, 16, "025_PIKACHU");
        m->addMove(Move("Quick Attack", ElementType::Normal, 15, 100));
        m->addMove(Move("Spark", ElementType::Electric, 22, 90));
        return m;
    } else if (key == "pidgey" || key == "016" || key == "016_pidgey") {
        auto m = std::make_shared<Monster>("Wild Pidgey", ElementType::Normal, level, 19, 11, 9, 13, "016_PIDGEY");
        m->addMove(Move("Tackle", ElementType::Normal, 14, 95));
        m->addMove(Move("Gust", ElementType::Normal, 18, 90));
        return m;
    } else if (key == "psyduck" || key == "054" || key == "054_psyduck") {
        auto m = std::make_shared<Monster>("Wild Psyduck", ElementType::Water, level, 23, 12, 10, 10, "054_PSYDUCK");
        m->addMove(Move("Scratch", ElementType::Normal, 14, 95));
        m->addMove(Move("Water Gun", ElementType::Water, 20, 90));
        return m;
    } else if (key == "poliwag" || key == "060" || key == "060_poliwag") {
        auto m = std::make_shared<Monster>("Wild Poliwag", ElementType::Water, level, 22, 11, 11, 14, "060_POLIWAG");
        m->addMove(Move("Pound", ElementType::Normal, 14, 95));
        m->addMove(Move("Water Gun", ElementType::Water, 20, 90));
        return m;
    } else if (key == "clefairy" || key == "035" || key == "035_clefairy") {
        auto m = std::make_shared<Monster>("Wild Clefairy", ElementType::Normal, level, 25, 11, 12, 9, "035_CLEFAIRY");
        m->addMove(Move("Pound", ElementType::Normal, 14, 95));
        m->addMove(Move("Disarming Voice", ElementType::Normal, 20, 100));
        return m;
    } else if (key == "eevee" || key == "133" || key == "133_eevee") {
        auto m = std::make_shared<Monster>("Wild Eevee", ElementType::Normal, level, 24, 13, 11, 12, "133_EEVEE");
        m->addMove(Move("Tackle", ElementType::Normal, 15, 95));
        m->addMove(Move("Quick Attack", ElementType::Normal, 16, 100));
        return m;
    } else if (key == "mewtwo" || key == "150" || key == "150_mewtwo" || key == "sylvanguard") {
        auto m = std::make_shared<Monster>("Mewtwo", ElementType::Grass, level, 55, 24, 18, 22, "150_MEWTWO");
        m->addMove(Move("Psystrike", ElementType::Grass, 30, 90));
        m->addMove(Move("Body Slam", ElementType::Normal, 24, 90));
        m->addMove(Move("Swift", ElementType::Normal, 22, 100));
        return m;
    }

    // Default fallback to Bulbasaur
    auto m = std::make_shared<Monster>("Wild Bulbasaur", ElementType::Grass, level, 22, 11, 11, 10, "001_BULBASAUR");
    m->addMove(Move("Tackle", ElementType::Normal, 14, 95));
    m->addMove(Move("Vine Whip", ElementType::Grass, 20, 90));
    return m;
}

std::shared_ptr<Monster> Monster::createWildMonster(int level, bool isBoss) {
    if (isBoss) {
        return createSpecificWildMonster("mewtwo", level);
    }

    static std::mt19937 rng(1337);
    int roll = rng() % 5;

    if (roll == 0) {
        return createSpecificWildMonster("bulbasaur", level);
    } else if (roll == 1) {
        return createSpecificWildMonster("pikachu", level);
    } else if (roll == 2) {
        return createSpecificWildMonster("pidgey", level);
    } else if (roll == 3) {
        return createSpecificWildMonster("psyduck", level);
    } else {
        return createSpecificWildMonster("poliwag", level);
    }
}
