#pragma once

#include "Common.hpp"
#include <string>
#include <vector>
#include <memory>

class Move {
private:
    std::string name;
    ElementType type;
    int power;
    int accuracy;

public:
    Move(std::string name, ElementType type, int power, int accuracy);

    const std::string& getName() const;
    ElementType getType() const;
    int getPower() const;
    int getAccuracy() const;
    std::string getTypeName() const;
};

class Monster {
private:
    std::string name;
    ElementType type;
    int level;
    int currentHp;
    int maxHp;
    int attack;
    int defense;
    int speed;
    int exp;
    int expToNextLevel;
    std::string textureKey;
    std::vector<Move> moves;

    void recalculateStats();

public:
    Monster(std::string name, ElementType type, int level, int baseHp, int baseAtk, int baseDef, int baseSpd, std::string textureKey);

    void addMove(const Move& move);

    int takeDamage(int movePower, ElementType moveType, const Monster& attacker, float& outMultiplier);
    void heal(int amount);
    void fullHeal();
    bool gainExp(int amount); // returns true if leveled up

    bool isFainted() const;

    // Encapsulated Getters
    const std::string& getName() const;
    ElementType getType() const;
    std::string getTypeName() const;
    int getLevel() const;
    int getCurrentHp() const;
    int getMaxHp() const;
    int getAttack() const;
    int getDefense() const;
    int getSpeed() const;
    int getExp() const;
    int getExpToNextLevel() const;
    const std::string& getTextureKey() const;
    const std::vector<Move>& getMoves() const;

    static float getTypeMultiplier(ElementType attackType, ElementType defenderType);
    static std::shared_ptr<Monster> createWildMonster(int level, bool isBoss = false);
    static std::shared_ptr<Monster> createSpecificWildMonster(const std::string& species, int level);
    static std::shared_ptr<Monster> createStarterMonster(int choice);
};
