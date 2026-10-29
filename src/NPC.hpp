#pragma once

#include "Character.hpp"
#include <string>
#include <vector>
#include <functional>

class GameStateManager;

// Base NPC Class (Polymorphism)
class NPC : public Character {
protected:
    std::string name;
    std::vector<std::string> dialogueLines;
    std::function<void(const std::string&, const std::vector<std::string>&)> dialogueTrigger;

public:
    NPC(int gridX, int gridY, const sf::Texture& texture, std::string name, Direction facing = Direction::Down);

    void setDialogueTrigger(std::function<void(const std::string&, const std::vector<std::string>&)> trigger);

    void onInteract(Player& player) override;
    bool isInteractive() const override { return true; }
    const std::string& getName() const { return name; }
};

// Derived NPC 1: Professor
class ProfessorNPC : public NPC {
private:
    std::function<void(int)> onStarterChosen;

public:
    ProfessorNPC(int gridX, int gridY, const sf::Texture& texture);
    void onInteract(Player& player) override;
    void setStarterCallback(std::function<void(int)> cb) { onStarterChosen = std::move(cb); }
};

// Derived NPC 2: Nurse Joy / Clinic Healer
class NurseNPC : public NPC {
public:
    NurseNPC(int gridX, int gridY, const sf::Texture& texture);
    void onInteract(Player& player) override;
};

// Derived NPC 3: Friendly Townsperson
class VillagerNPC : public NPC {
public:
    VillagerNPC(int gridX, int gridY, const sf::Texture& texture);
    void onInteract(Player& player) override;
};

// Derived NPC 4: Forest Guardian Boss
class BossNPC : public NPC {
private:
    std::function<void()> onBossBattleTriggered;

public:
    BossNPC(int gridX, int gridY, const sf::Texture& texture);
    void onInteract(Player& player) override;
    void setBossTrigger(std::function<void()> cb) { onBossBattleTriggered = std::move(cb); }
};
