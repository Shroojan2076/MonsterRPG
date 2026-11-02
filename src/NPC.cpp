#include "NPC.hpp"
#include "Player.hpp"

// NPC Base
NPC::NPC(int gridX, int gridY, const sf::Texture& texture, std::string name, Direction facing)
    : Character(gridX, gridY, texture, facing), name(std::move(name)) {}

void NPC::onInteract(Player& player) {
    // Face towards the player
    sf::Vector2i pPos = player.getGridPosition();
    if (pPos.y < gridPosition.y) turnTo(Direction::Up);
    else if (pPos.y > gridPosition.y) turnTo(Direction::Down);
    else if (pPos.x < gridPosition.x) turnTo(Direction::Left);
    else if (pPos.x > gridPosition.x) turnTo(Direction::Right);

    if (!dialogueLines.empty()) {
        triggerDialogue(name, dialogueLines);
    }
}

// ProfessorNPC
ProfessorNPC::ProfessorNPC(int gridX, int gridY, const sf::Texture& texture)
    : NPC(gridX, gridY, texture, "Prof. Oak", Direction::Down) {}

void ProfessorNPC::onInteract(Player& player) {
    NPC::onInteract(player);

    if (!player.hasStarter()) {
        // Entrust player with starter Charmander
        player.addMonster(Monster::createStarterMonster(1));
        player.setHasStarter(true);

        std::vector<std::string> lines = {
            "Hello young adventurer! Welcome to Oakdale Town.",
            "The forest east of here is teeming with mysterious Pokemon.",
            "I have entrusted you with a brave Charmander (Fire-type)!",
            "Take these Potions and Poke Balls from your bag.",
            "Go explore Whispering Woods and investigate the legendary Pokemon sighted in the clearing!"
        };
        triggerDialogue(name, lines);
    } else if (player.isBossDefeated()) {
        std::vector<std::string> lines = {
            "Incredible! You quelled the psychic powerhouse Mewtwo!",
            "You are a true Pokemon Champion! Oakdale is forever grateful!"
        };
        triggerDialogue(name, lines);
    } else {
        std::vector<std::string> lines = {
            "How is Charmander doing? Remember to train in the tall grass.",
            "When wild Pokemon are weakened, throw a Poke Ball to catch them!"
        };
        triggerDialogue(name, lines);
    }
}

// NurseNPC
NurseNPC::NurseNPC(int gridX, int gridY, const sf::Texture& texture)
    : NPC(gridX, gridY, texture, "Nurse Joy", Direction::Down) {}

void NurseNPC::onInteract(Player& player) {
    NPC::onInteract(player);

    player.healAllMonsters();

    std::vector<std::string> lines = {
        "Welcome to the Pokemon Center!",
        "Your Pokemon look exhausted... let me care for them.",
        "... ... ...",
        "Your Pokemon party has been completely restored to full health!",
        "We hope to see you again. Stay safe out there!"
    };
    triggerDialogue(name, lines);
}

// VillagerNPC
VillagerNPC::VillagerNPC(int gridX, int gridY, const sf::Texture& texture)
    : NPC(gridX, gridY, texture, "Cedric", Direction::Right) {}

void VillagerNPC::onInteract(Player& player) {
    NPC::onInteract(player);

    std::vector<std::string> lines = {
        "Did you hear the whispers in the woods to the east?",
        "Fire burns Grass, Water douses Fire, and Grass absorbs Water!",
        "Watch your steps in dark tall grass - wild Pokemon pounce unexpectedly!"
    };
    triggerDialogue(name, lines);
}

// BossNPC
BossNPC::BossNPC(int gridX, int gridY, const sf::Texture& texture)
    : NPC(gridX, gridY, texture, "Mewtwo", Direction::Down) {}

void BossNPC::onInteract(Player& player) {
    NPC::onInteract(player);

    if (player.isBossDefeated()) {
        std::vector<std::string> lines = {
            "Mewtwo rests peacefully, communing with the forest sunlight."
        };
        triggerDialogue(name, lines);
    } else {
        std::vector<std::string> lines = {
            "The legendary Pokemon Mewtwo radiates overwhelming psychic energy!",
            "Mewtwo: 'Mew... TWO!'",
            "Prepare for battle!"
        };
        triggerDialogue(name, lines, onBossBattleTriggered);
    }
}
