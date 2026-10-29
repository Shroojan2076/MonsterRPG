#include "NPC.hpp"
#include "Player.hpp"

// NPC Base
NPC::NPC(int gridX, int gridY, const sf::Texture& texture, std::string name, Direction facing)
    : Character(gridX, gridY, texture, facing), name(std::move(name)) {}

void NPC::setDialogueTrigger(std::function<void(const std::string&, const std::vector<std::string>&)> trigger) {
    dialogueTrigger = std::move(trigger);
}

void NPC::onInteract(Player& player) {
    // Face towards the player
    sf::Vector2i pPos = player.getGridPosition();
    if (pPos.y < gridPosition.y) turnTo(Direction::Up);
    else if (pPos.y > gridPosition.y) turnTo(Direction::Down);
    else if (pPos.x < gridPosition.x) turnTo(Direction::Left);
    else if (pPos.x > gridPosition.x) turnTo(Direction::Right);

    if (dialogueTrigger && !dialogueLines.empty()) {
        dialogueTrigger(name, dialogueLines);
    }
}

// ProfessorNPC
ProfessorNPC::ProfessorNPC(int gridX, int gridY, const sf::Texture& texture)
    : NPC(gridX, gridY, texture, "Prof. Oak", Direction::Down) {}

void ProfessorNPC::onInteract(Player& player) {
    NPC::onInteract(player);

    if (!player.hasStarter()) {
        // Give player a starter monster (Pyropup) and starter gear
        player.addMonster(Monster::createStarterMonster(1)); // Pyropup
        player.setHasStarter(true);

        std::vector<std::string> lines = {
            "Hello young adventurer! Welcome to Oakdale Town.",
            "The forest east of here is teeming with mysterious monsters.",
            "I have entrusted you with a brave Pyropup (Fire-type)!",
            "Take these Potions and Capture Balls from your bag.",
            "Go explore Whispering Woods and investigate the Forest Guardian!"
        };
        if (dialogueTrigger) dialogueTrigger(name, lines);
    } else if (player.isBossDefeated()) {
        std::vector<std::string> lines = {
            "Incredible! You quelled the raging Sylvanguard!",
            "You are a true Monster Champion! Oakdale is forever grateful!"
        };
        if (dialogueTrigger) dialogueTrigger(name, lines);
    } else {
        std::vector<std::string> lines = {
            "How is Pyropup doing? Remember to train in the tall grass.",
            "When wild monsters are weakened, throw a Capture Ball to catch them!"
        };
        if (dialogueTrigger) dialogueTrigger(name, lines);
    }
}

// NurseNPC
NurseNPC::NurseNPC(int gridX, int gridY, const sf::Texture& texture)
    : NPC(gridX, gridY, texture, "Nurse Joy", Direction::Down) {}

void NurseNPC::onInteract(Player& player) {
    NPC::onInteract(player);

    player.healAllMonsters();

    std::vector<std::string> lines = {
        "Welcome to the Oakdale Health Center!",
        "Your monsters look exhausted... let me care for them.",
        "... ... ...",
        "Your monster party has been completely restored to full health!",
        "We hope to see you again. Stay safe out there!"
    };
    if (dialogueTrigger) dialogueTrigger(name, lines);
}

// VillagerNPC
VillagerNPC::VillagerNPC(int gridX, int gridY, const sf::Texture& texture)
    : NPC(gridX, gridY, texture, "Cedric", Direction::Right) {}

void VillagerNPC::onInteract(Player& player) {
    NPC::onInteract(player);

    std::vector<std::string> lines = {
        "Did you hear the whispers in the woods to the east?",
        "Fire burns Grass, Water douses Fire, and Grass absorbs Water!",
        "Watch your steps in dark tall grass - creatures pounce unexpectedly!"
    };
    if (dialogueTrigger) dialogueTrigger(name, lines);
}

// BossNPC
BossNPC::BossNPC(int gridX, int gridY, const sf::Texture& texture)
    : NPC(gridX, gridY, texture, "Sylvanguard", Direction::Down) {}

void BossNPC::onInteract(Player& player) {
    NPC::onInteract(player);

    if (player.isBossDefeated()) {
        std::vector<std::string> lines = {
            "Sylvanguard rests peacefully, bathing in the forest sunlight."
        };
        if (dialogueTrigger) dialogueTrigger(name, lines);
    } else {
        std::vector<std::string> lines = {
            "The mighty Forest Guardian Sylvanguard bellows with primal energy!",
            "Prepare for battle!"
        };
        if (dialogueTrigger) {
            dialogueTrigger(name, lines);
        }
        if (onBossBattleTriggered) {
            onBossBattleTriggered();
        }
    }
}
