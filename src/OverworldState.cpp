#include "OverworldState.hpp"
#include "StateManager.hpp"
#include "DialogueState.hpp"
#include "BattleState.hpp"
#include "ResourceManager.hpp"
#include "NPC.hpp"
#include "WorldObject.hpp"
#include <algorithm>
#include <random>

OverworldState::OverworldState(StateManager& manager, const ResourceManager& res)
    : GameState(manager),
      resources(res),
      tileMap(res.getWorldTileset()),
      player(10, 13, res.getPlayerTexture(), res.getPlayerRunTexture()), // Spawn at town square
      gameView(sf::FloatRect({0.0f, 0.0f}, {VIEW_WIDTH, VIEW_HEIGHT})) {
    initializeEntities();

    // Collision check: prevent player from walking through solid NPCs and objects
    player.setCollisionCallback([this](int x, int y) {
        for (const auto& entity : entities) {
            if (entity->isSolid() && entity->getGridPosition().x == x && entity->getGridPosition().y == y) {
                return true;
            }
        }
        return false;
    });

    // Hook step completed event for wild monster encounters
    player.setOnStepCompleted([this](sf::Vector2i pos) {
        checkWildEncounter(pos);
    });
}

void OverworldState::initializeEntities() {
    auto dialogueCallback = [this](const std::string& speaker, const std::vector<std::string>& lines) {
        stateManager.pushState(std::make_unique<DialogueState>(stateManager, resources, speaker, lines));
    };

    // 1. Professor Oak at Town Lab
    auto prof = std::make_unique<ProfessorNPC>(6, 8, resources.getNpcProfTexture());
    prof->setDialogueTrigger(dialogueCallback);
    entities.push_back(std::move(prof));

    // 2. Nurse Joy at Town Clinic
    auto nurse = std::make_unique<NurseNPC>(6, 19, resources.getNpcNurseTexture());
    nurse->setDialogueTrigger(dialogueCallback);
    entities.push_back(std::move(nurse));

    // 3. Cedric the Villager at Town Square
    auto villager = std::make_unique<VillagerNPC>(13, 11, resources.getNpcVillagerTexture());
    villager->setDialogueTrigger(dialogueCallback);
    entities.push_back(std::move(villager));

    // 4. Forest Guardian Boss Sylvanguard
    auto boss = std::make_unique<BossNPC>(37, 5, resources.getMonsterTexture("sylvanguard"));
    boss->setDialogueTrigger(dialogueCallback);
    boss->setBossTrigger([this]() {
        auto bossMonster = Monster::createWildMonster(10, true);
        stateManager.pushState(std::make_unique<BattleState>(stateManager, player, bossMonster, resources, true));
    });
    entities.push_back(std::move(boss));

    // 5. Town Signpost
    auto townSign = std::make_unique<Signpost>(14, 11, "Oakdale Sign", std::vector<std::string>{
        "[ Oakdale Town ]",
        "A peaceful haven where nature thrives and new journeys ignite!"
    });
    townSign->setDialogueTrigger(dialogueCallback);
    entities.push_back(std::move(townSign));

    // 6. Forest Warning Signpost
    auto forestSign = std::make_unique<Signpost>(22, 11, "Forest Sign", std::vector<std::string>{
        "[ Whispering Woods Ahead ]",
        "CAUTION: Wild monsters roam in the dark grass!",
        "Ensure your team is healed before proceeding."
    });
    forestSign->setDialogueTrigger(dialogueCallback);
    entities.push_back(std::move(forestSign));

    // 7. Hidden Item Ball in the Woods
    auto itemBall = std::make_unique<ItemBall>(38, 22, resources.getWorldTileset());
    itemBall->setDialogueTrigger(dialogueCallback);
    entities.push_back(std::move(itemBall));
}

void OverworldState::handleInput(const sf::Event& event) {
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::E ||
            keyPressed->code == sf::Keyboard::Key::Space ||
            keyPressed->code == sf::Keyboard::Key::Enter) {
            handleInteraction();
        }
    }
}

void OverworldState::handleInteraction() {
    sf::Vector2i targetPos = player.getFrontTile();

    for (auto& entity : entities) {
        if (entity->getGridPosition() == targetPos && entity->isInteractive()) {
            entity->onInteract(player);
            return;
        }
    }

    // Also check current tile (for item pickups that player can stand on)
    sf::Vector2i currentPos = player.getGridPosition();
    for (auto& entity : entities) {
        if (entity->getGridPosition() == currentPos && entity->isInteractive()) {
            entity->onInteract(player);
            return;
        }
    }
}

void OverworldState::checkWildEncounter(sf::Vector2i playerGridPos) {
    if (!tileMap.isTallGrass(playerGridPos.x, playerGridPos.y)) {
        return;
    }

    // Must have a starter monster and an alive monster to fight
    if (!player.hasStarter() || player.getFirstAliveMonster() == nullptr) {
        return;
    }

    // 18% encounter chance per step in tall grass
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 100);

    if (dist(rng) <= 18) {
        // Roll wild monster level (3 to 6)
        std::uniform_int_distribution<int> lvlDist(3, 6);
        int wildLevel = lvlDist(rng);
        auto wildMonster = Monster::createWildMonster(wildLevel, false);

        stateManager.pushState(std::make_unique<BattleState>(stateManager, player, wildMonster, resources, false));
    }
}

void OverworldState::update(float deltaTime) {
    player.update(deltaTime, tileMap);

    for (auto& entity : entities) {
        entity->update(deltaTime, tileMap);
    }
}

void OverworldState::render(sf::RenderTarget& target) {
    // 1. Center camera on player with smooth world boundary clamping
    sf::Vector2f cameraCenter = player.getWorldPosition();
    float halfWidth = VIEW_WIDTH / 2.0f;
    float halfHeight = VIEW_HEIGHT / 2.0f;

    float worldWidth = static_cast<float>(tileMap.getWidth() * tileMap.getTileSize());
    float worldHeight = static_cast<float>(tileMap.getHeight() * tileMap.getTileSize());

    cameraCenter.x = std::max(halfWidth, std::min(cameraCenter.x, worldWidth - halfWidth));
    cameraCenter.y = std::max(halfHeight, std::min(cameraCenter.y, worldHeight - halfHeight));

    gameView.setCenter(cameraCenter);
    target.setView(gameView);

    // 2. Render TileMap
    tileMap.draw(target);

    // 3. Render Entities (Y-sorted for proper depth)
    std::vector<Entity*> renderList;
    renderList.push_back(&player);
    for (auto& e : entities) {
        renderList.push_back(e.get());
    }

    std::sort(renderList.begin(), renderList.end(), [](Entity* a, Entity* b) {
        return a->getWorldPosition().y < b->getWorldPosition().y;
    });

    for (auto* e : renderList) {
        e->draw(target);
    }

    // 4. Overworld UI HUD in Screen Space
    sf::View worldView = target.getView();
    target.setView(target.getDefaultView()); // 960x640

    // Top control hint banner
    sf::RectangleShape hintBar({960.0f, 32.0f});
    hintBar.setFillColor(sf::Color(10, 15, 25, 200));
    target.draw(hintBar);

    std::string hudInfo = " [WASD] Move / Tap to Turn   |   [Shift] Run   |   [E / Space] Talk / Interact";
    if (player.hasStarter()) {
        auto m = player.getFirstAliveMonster();
        if (m) {
            hudInfo += "   |   Partner: " + m->getName() + " (Lv. " + std::to_string(m->getLevel()) + " - HP: " +
                       std::to_string(m->getCurrentHp()) + "/" + std::to_string(m->getMaxHp()) + ")";
        }
    } else {
        hudInfo += "   |   Visit Prof. Oak in the Lab (North-West) to get a Starter!";
    }

    sf::Text hintText(resources.getFont(), hudInfo, 14);
    hintText.setFillColor(sf::Color(240, 240, 245, 240));
    hintText.setPosition({15.0f, 6.0f});
    target.draw(hintText);

    target.setView(worldView); // Restore
}
