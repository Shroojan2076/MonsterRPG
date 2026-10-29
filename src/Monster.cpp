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
        auto m = std::make_shared<Monster>("Pyropup", ElementType::Fire, 5, 24, 14, 10, 12, "pyropup");
        m->addMove(Move("Tackle", ElementType::Normal, 15, 95));
        m->addMove(Move("Ember", ElementType::Fire, 22, 90));
        return m;
    } else if (choice == 2) { // Water
        auto m = std::make_shared<Monster>("Aquafox", ElementType::Water, 5, 26, 12, 12, 11, "aquafox");
        m->addMove(Move("Tackle", ElementType::Normal, 15, 95));
        m->addMove(Move("Water Gun", ElementType::Water, 22, 90));
        return m;
    } else { // Grass
        auto m = std::make_shared<Monster>("Grassling", ElementType::Grass, 5, 28, 11, 13, 10, "grassling");
        m->addMove(Move("Tackle", ElementType::Normal, 15, 95));
        m->addMove(Move("Vine Whip", ElementType::Grass, 22, 90));
        return m;
    }
}

std::shared_ptr<Monster> Monster::createWildMonster(int level, bool isBoss) {
    if (isBoss) {
        auto m = std::make_shared<Monster>("Sylvanguard", ElementType::Grass, level, 45, 18, 16, 14, "sylvanguard");
        m->addMove(Move("Mega Drain", ElementType::Grass, 25, 90));
        m->addMove(Move("Horn Leech", ElementType::Grass, 30, 85));
        m->addMove(Move("Body Slam", ElementType::Normal, 22, 90));
        return m;
    }

    static std::mt19937 rng(42);
    int roll = rng() % 3;

    if (roll == 0) {
        auto m = std::make_shared<Monster>("Wild Grassling", ElementType::Grass, level, 20, 10, 9, 8, "grassling");
        m->addMove(Move("Tackle", ElementType::Normal, 12, 95));
        m->addMove(Move("Leaf Cut", ElementType::Grass, 18, 90));
        return m;
    } else if (roll == 1) {
        auto m = std::make_shared<Monster>("Wild Voltmouse", ElementType::Electric, level, 18, 12, 7, 14, "voltmouse");
        m->addMove(Move("Quick Attack", ElementType::Normal, 12, 100));
        m->addMove(Move("Spark", ElementType::Electric, 20, 90));
        return m;
    } else {
        auto m = std::make_shared<Monster>("Wild Aquafox", ElementType::Water, level, 22, 10, 10, 9, "aquafox");
        m->addMove(Move("Scratch", ElementType::Normal, 12, 95));
        m->addMove(Move("Bubble", ElementType::Water, 18, 90));
        return m;
    }
}
