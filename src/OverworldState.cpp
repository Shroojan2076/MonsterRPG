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
      follower(10, 14, res),
      activeEntities(&overworldEntities),
      transitionState(TransitionState::None),
      transitionAlpha(0.0f),
      pendingMapId(MapId::Overworld),
      pendingTargetPos({10, 13}),
      pendingTargetDir(Direction::Down),
      gameView(sf::FloatRect({0.0f, 0.0f}, {VIEW_WIDTH, VIEW_HEIGHT})) {
    initializeEntities();

    // Collision check: prevent player from walking through solid NPCs and objects on active map
    player.setCollisionCallback([this](int x, int y) {
        if (!activeEntities) return false;
        for (const auto& entity : *activeEntities) {
            if (entity->isSolid() && entity->getGridPosition().x == x && entity->getGridPosition().y == y) {
                return true;
            }
        }
        return false;
    });

    // Hook step completed event for follower step, warp triggers, and wild monster encounters
    player.setOnStepCompleted([this](sf::Vector2i pos) {
        follower.onPlayerStep(player.getPreviousGridPosition(), player.getFacingDirection());
        if (checkWarpTrigger(pos)) {
            return;
        }
        checkWildEncounter(pos);
    });
}

void OverworldState::initializeEntities() {
    auto dialogueCallback = [this](const std::string& speaker, const std::vector<std::string>& lines, std::function<void()> onComplete) {
        stateManager.pushState(std::make_unique<DialogueState>(stateManager, resources, speaker, lines, std::move(onComplete)));
    };
    auto simpleDialogueCallback = [this](const std::string& speaker, const std::vector<std::string>& lines) {
        stateManager.pushState(std::make_unique<DialogueState>(stateManager, resources, speaker, lines));
    };

    follower.setDialogueTrigger(dialogueCallback);

    // =========================================================================
    // 1. OVERWORLD ENTITIES (Town & Whispering Woods)
    // NOTE: Professor Oak and Nurse Joy are placed INSIDE their own buildings!
    // =========================================================================
    // Cedric the Villager at Town Square
    auto villager = std::make_unique<VillagerNPC>(13, 11, resources.getNpcVillagerTexture());
    villager->setDialogueTrigger(dialogueCallback);
    overworldEntities.push_back(std::move(villager));

    // Cedric's companion Meowth
    auto meowth = std::make_unique<PokemonEntity>(12, 11, resources.getPokemonOverworldTexture("052_MEOWTH"), "Meowth", "052_MEOWTH");
    meowth->setDialogue({
        "Meowth: 'Nya-ha-ha! Purrr!'",
        "Cedric's friendly Meowth playfully taps its shiny gold coin."
    });
    meowth->setDialogueTrigger(dialogueCallback);
    overworldEntities.push_back(std::move(meowth));

    // Town Signpost
    auto townSign = std::make_unique<Signpost>(14, 11, "Oakdale Sign", std::vector<std::string>{
        "[ Oakdale Town ]",
        "A peaceful haven where nature thrives and new journeys ignite!"
    });
    townSign->setDialogueTrigger(simpleDialogueCallback);
    overworldEntities.push_back(std::move(townSign));

    // Forest Warning Signpost
    auto forestSign = std::make_unique<Signpost>(22, 11, "Forest Sign", std::vector<std::string>{
        "[ Whispering Woods Ahead ]",
        "CAUTION: Wild Pokemon roam in the tall grass!",
        "Ensure your team is healed before proceeding."
    });
    forestSign->setDialogueTrigger(simpleDialogueCallback);
    overworldEntities.push_back(std::move(forestSign));

    // Hidden Item Ball in the Woods
    auto itemBall = std::make_unique<ItemBall>(38, 22, resources.getWorldTileset());
    itemBall->setDialogueTrigger(simpleDialogueCallback);
    overworldEntities.push_back(std::move(itemBall));

    // Sleeping Snorlax in peaceful forest grove at (36, 12)
    auto snorlax = std::make_unique<PokemonEntity>(36, 12, resources.getPokemonOverworldTexture("143_SNORLAX"), "Snorlax", "143_SNORLAX");
    snorlax->setDialogue({
        "Snorlax: 'Zzzzzzz... Snork...'",
        "A huge Snorlax is blissfully snoozing in the shade, completely unbothered by the world.",
        "Its deep, rhythmic snores reverberate through the clearing."
    });
    snorlax->setDialogueTrigger(dialogueCallback);
    overworldEntities.push_back(std::move(snorlax));

    // Wild Pikachu in tall grass nook at (25, 7)
    auto pika = std::make_unique<PokemonEntity>(25, 7, resources.getPokemonOverworldTexture("025_PIKACHU"), "Pikachu", "025_PIKACHU", true);
    pika->setDialogue({
        "Pikachu: 'Pika-pika! Pi-ka-chuuu!'",
        "The wild Pikachu crackles with playful electricity and challenges you to battle!"
    });
    pika->setDialogueTrigger(dialogueCallback);
    pika->setBattleTrigger([this, pikaPtr = pika.get()]() {
        if (!player.hasStarter()) return;
        auto wildPika = Monster::createSpecificWildMonster("025", 5);
        stateManager.pushState(std::make_unique<BattleState>(stateManager, player, wildPika, resources, false));
        pikaPtr->setDefeatedOrCaught(true);
    });
    overworldEntities.push_back(std::move(pika));

    // Wild Bulbasaur under canopy at (21, 17)
    auto bulba = std::make_unique<PokemonEntity>(21, 17, resources.getPokemonOverworldTexture("001_BULBASAUR"), "Bulbasaur", "001_BULBASAUR", true);
    bulba->setDialogue({
        "Bulbasaur: 'Bulba-saur!'",
        "A wild Bulbasaur rustles through the foliage and leaps forward!"
    });
    bulba->setDialogueTrigger(dialogueCallback);
    bulba->setBattleTrigger([this, bulbaPtr = bulba.get()]() {
        if (!player.hasStarter()) return;
        auto wildBulba = Monster::createSpecificWildMonster("001", 5);
        stateManager.pushState(std::make_unique<BattleState>(stateManager, player, wildBulba, resources, false));
        bulbaPtr->setDefeatedOrCaught(true);
    });
    overworldEntities.push_back(std::move(bulba));

    // Wild Pidgey on trail at (31, 15)
    auto pidgey = std::make_unique<PokemonEntity>(31, 15, resources.getPokemonOverworldTexture("016_PIDGEY"), "Pidgey", "016_PIDGEY", true);
    pidgey->setDialogue({
        "Pidgey: 'Pidgey-pidge!'",
        "A wild Pidgey swoops down from the treetops!"
    });
    pidgey->setDialogueTrigger(dialogueCallback);
    pidgey->setBattleTrigger([this, pidgeyPtr = pidgey.get()]() {
        if (!player.hasStarter()) return;
        auto wildPidgey = Monster::createSpecificWildMonster("016", 4);
        stateManager.pushState(std::make_unique<BattleState>(stateManager, player, wildPidgey, resources, false));
        pidgeyPtr->setDefeatedOrCaught(true);
    });
    overworldEntities.push_back(std::move(pidgey));

    // Wild Psyduck near water clearing at (26, 21)
    auto psyduck = std::make_unique<PokemonEntity>(26, 21, resources.getPokemonOverworldTexture("054_PSYDUCK"), "Psyduck", "054_PSYDUCK", true);
    psyduck->setDialogue({
        "Psyduck: 'Psy... duck?'",
        "Psyduck clutches its head and tilts to one side, looking startled!"
    });
    psyduck->setDialogueTrigger(dialogueCallback);
    psyduck->setBattleTrigger([this, psyduckPtr = psyduck.get()]() {
        if (!player.hasStarter()) return;
        auto wildPsyduck = Monster::createSpecificWildMonster("054", 4);
        stateManager.pushState(std::make_unique<BattleState>(stateManager, player, wildPsyduck, resources, false));
        psyduckPtr->setDefeatedOrCaught(true);
    });
    overworldEntities.push_back(std::move(psyduck));

    // Wild Poliwag by the stream at (34, 19)
    auto poliwag = std::make_unique<PokemonEntity>(34, 19, resources.getPokemonOverworldTexture("060_POLIWAG"), "Poliwag", "060_POLIWAG", true);
    poliwag->setDialogue({
        "Poliwag: 'Poli-poli!'",
        "A wild Poliwag splashes out of the pond onto the shore!"
    });
    poliwag->setDialogueTrigger(dialogueCallback);
    poliwag->setBattleTrigger([this, poliwagPtr = poliwag.get()]() {
        if (!player.hasStarter()) return;
        auto wildPoliwag = Monster::createSpecificWildMonster("060", 4);
        stateManager.pushState(std::make_unique<BattleState>(stateManager, player, wildPoliwag, resources, false));
        poliwagPtr->setDefeatedOrCaught(true);
    });
    overworldEntities.push_back(std::move(poliwag));

    // Boss Mewtwo at (37, 5) using authentic 32x32 Pokemon sprite
    auto boss = std::make_unique<PokemonEntity>(37, 5, resources.getPokemonOverworldTexture("150_MEWTWO"), "Mewtwo", "150_MEWTWO");
    boss->setCustomInteract([this](Player& p) {
        if (p.isBossDefeated()) {
            stateManager.pushState(std::make_unique<DialogueState>(stateManager, resources, "Mewtwo", std::vector<std::string>{
                "Mewtwo rests peacefully, communing with the forest sunlight."
            }));
        } else {
            stateManager.pushState(std::make_unique<DialogueState>(stateManager, resources, "Mewtwo", std::vector<std::string>{
                "The legendary Pokemon Mewtwo radiates overwhelming psychic energy!",
                "Mewtwo: 'Mew... TWO!'",
                "Prepare for battle!"
            }, [this]() {
                auto bossMonster = Monster::createWildMonster(10, true);
                stateManager.pushState(std::make_unique<BattleState>(stateManager, player, bossMonster, resources, true));
            }));
        }
    });
    overworldEntities.push_back(std::move(boss));

    // =========================================================================
    // 2. PROFESSOR OAK'S LAB ENTITIES (Interior)
    // =========================================================================
    // Professor Oak NPC at research table (Grid 6, 3 facing Down)
    auto prof = std::make_unique<ProfessorNPC>(6, 3, resources.getNpcProfTexture());
    prof->setDialogueTrigger(dialogueCallback);
    oakLabEntities.push_back(std::move(prof));

    // Research Whiteboard at (6, 2)
    auto whiteboard = std::make_unique<Signpost>(6, 2, "Research Board", std::vector<std::string>{
        "[ Research Whiteboard ]",
        "Formulas detailing elemental affinities and creature evolutions.",
        "'Fire scorches Grass, Water extinguishes Fire, Grass absorbs Water!'"
    });
    whiteboard->setDialogueTrigger(simpleDialogueCallback);
    oakLabEntities.push_back(std::move(whiteboard));

    // Lab Computer Mainframe at (4, 3)
    auto labPC = std::make_unique<Signpost>(4, 3, "Lab Terminal", std::vector<std::string>{
        "[ Oak's Mainframe Terminal ]",
        "Accessing Pokemon habitat telemetry...",
        "Wild specimens in Whispering Woods: Bulbasaur, Charmander, Squirtle, Pikachu, Mewtwo."
    });
    labPC->setDialogueTrigger(simpleDialogueCallback);
    oakLabEntities.push_back(std::move(labPC));

    // Oak's assistant Eevee at (9, 3)
    auto eevee = std::make_unique<PokemonEntity>(9, 3, resources.getPokemonOverworldTexture("133_EEVEE"), "Eevee", "133_EEVEE");
    eevee->setDialogue({
        "Eevee: 'Eev-vee!'",
        "Prof. Oak's assistant Eevee is happily reviewing some research notes.",
        "It wags its fluffy tail cheerfully."
    });
    eevee->setDialogueTrigger(dialogueCallback);
    oakLabEntities.push_back(std::move(eevee));

    // Starter Squirtle companion at (3, 5)
    auto squirtle = std::make_unique<PokemonEntity>(3, 5, resources.getPokemonOverworldTexture("007_SQUIRTLE"), "Squirtle", "007_SQUIRTLE");
    squirtle->setDialogue({
        "Squirtle: 'Squirtle-turtle!'",
        "Squirtle is admiring its shiny shell in the reflection of a glass beaker."
    });
    squirtle->setDialogueTrigger(dialogueCallback);
    oakLabEntities.push_back(std::move(squirtle));

    // =========================================================================
    // 3. POKÉMON CLINIC ENTITIES (Interior)
    // =========================================================================
    // Nurse Joy NPC behind service counter (Grid 6, 3 facing Down)
    auto nurse = std::make_unique<NurseNPC>(6, 3, resources.getNpcNurseTexture());
    nurse->setDialogueTrigger(dialogueCallback);
    pokemonCenterEntities.push_back(std::move(nurse));

    // Nurse Joy's assistant Clefairy at (7, 3)
    auto clefairy = std::make_unique<PokemonEntity>(7, 3, resources.getPokemonOverworldTexture("035_CLEFAIRY"), "Clefairy", "035_CLEFAIRY");
    clefairy->setDialogue({
        "Clefairy: 'Clef-fairy!'",
        "Nurse Joy's assistant Clefairy greets you with a warm, comforting smile."
    });
    clefairy->setDialogueTrigger(dialogueCallback);
    pokemonCenterEntities.push_back(std::move(clefairy));

    // Visiting Jigglypuff at (4, 6)
    auto jigglypuff = std::make_unique<PokemonEntity>(4, 6, resources.getPokemonOverworldTexture("039_JIGGLYPUFF"), "Jigglypuff", "039_JIGGLYPUFF");
    jigglypuff->setDialogue({
        "Jigglypuff: 'Jiggly... puff!'",
        "A visiting Jigglypuff is resting on the lounge mat, softly humming a melodic tune."
    });
    jigglypuff->setDialogueTrigger(dialogueCallback);
    pokemonCenterEntities.push_back(std::move(jigglypuff));

    // Trainer Storage PC Terminal at (10, 2)
    auto trainerPC = std::make_unique<Signpost>(10, 2, "Trainer PC", std::vector<std::string>{
        "[ Oakdale Storage System ]",
        "Oakdale Network Storage Terminal.",
        "All Pokemon storage systems are operating normally."
    });
    trainerPC->setDialogueTrigger(simpleDialogueCallback);
    pokemonCenterEntities.push_back(std::move(trainerPC));

    // Vending Machines at (2, 4)
    auto vending = std::make_unique<Signpost>(2, 4, "Vending Machine", std::vector<std::string>{
        "[ Refreshment Vending Machine ]",
        "Stocked with Fresh Water, Soda Pop, and Lemonade!",
        "Healthy refreshments for weary traveling companions."
    });
    vending->setDialogueTrigger(simpleDialogueCallback);
    pokemonCenterEntities.push_back(std::move(vending));

    // Default active entities
    activeEntities = &overworldEntities;
}

bool OverworldState::checkWarpTrigger(sf::Vector2i playerGridPos) {
    if (transitionState != TransitionState::None) return false;

    MapId currentMap = tileMap.getCurrentMapId();

    if (currentMap == MapId::Overworld) {
        // Lab Door at (6, 7) -> warp inside OakLab at (6, 8) facing Up
        if (playerGridPos == sf::Vector2i(6, 7)) {
            startWarp(MapId::OakLab, sf::Vector2i(6, 8), Direction::Up);
            return true;
        }
        // Clinic Door at (6, 18) -> warp inside PokemonCenter at (6, 8) facing Up
        if (playerGridPos == sf::Vector2i(6, 18)) {
            startWarp(MapId::PokemonCenter, sf::Vector2i(6, 8), Direction::Up);
            return true;
        }
    } else if (currentMap == MapId::OakLab) {
        // Exit Mat at (6, 9) -> warp to Overworld at (6, 8) facing Down
        if (playerGridPos == sf::Vector2i(6, 9)) {
            startWarp(MapId::Overworld, sf::Vector2i(6, 8), Direction::Down);
            return true;
        }
    } else if (currentMap == MapId::PokemonCenter) {
        // Exit Mat at (6, 9) -> warp to Overworld at (6, 19) facing Down
        if (playerGridPos == sf::Vector2i(6, 9)) {
            startWarp(MapId::Overworld, sf::Vector2i(6, 19), Direction::Down);
            return true;
        }
    }

    return false;
}

void OverworldState::startWarp(MapId targetMap, sf::Vector2i targetPos, Direction targetDir) {
    transitionState = TransitionState::FadingOut;
    transitionAlpha = 0.0f;
    pendingMapId = targetMap;
    pendingTargetPos = targetPos;
    pendingTargetDir = targetDir;
}

void OverworldState::executeWarp(MapId targetMap, sf::Vector2i targetPos, Direction targetDir) {
    tileMap.loadMap(targetMap);
    switch (targetMap) {
        case MapId::Overworld:
            activeEntities = &overworldEntities;
            break;
        case MapId::OakLab:
            activeEntities = &oakLabEntities;
            break;
        case MapId::PokemonCenter:
            activeEntities = &pokemonCenterEntities;
            break;
    }
    player.teleport(targetPos.x, targetPos.y, targetDir);
    follower.teleport(targetPos.x, targetPos.y);
    follower.syncWithPlayer(player);
}

void OverworldState::handleInput(const sf::Event& event) {
    if (transitionState != TransitionState::None) {
        return; // Ignore interaction input while warping
    }

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

    // 0. Follower partner Pokémon interaction
    if (follower.isActive() && follower.getGridPosition() == targetPos) {
        follower.onInteract(player);
        return;
    }

    if (!activeEntities) return;

    // 1. Direct interaction (NPC right in front or object on target tile)
    for (auto& entity : *activeEntities) {
        if (entity->getGridPosition() == targetPos && entity->isInteractive()) {
            entity->onInteract(player);
            return;
        }
    }

    // 2. Interaction across counter / desk (1 tile behind target if target is counter/desk)
    sf::Vector2i acrossPos = targetPos + directionToOffset(player.getFacingDirection());
    for (auto& entity : *activeEntities) {
        if (entity->getGridPosition() == acrossPos && entity->isInteractive()) {
            entity->onInteract(player);
            return;
        }
    }

    // 3. Current tile underfoot interaction (e.g. standing on items)
    sf::Vector2i currentPos = player.getGridPosition();
    for (auto& entity : *activeEntities) {
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
    if (transitionState == TransitionState::FadingOut) {
        transitionAlpha += TRANSITION_SPEED * deltaTime;
        if (transitionAlpha >= 255.0f) {
            transitionAlpha = 255.0f;
            executeWarp(pendingMapId, pendingTargetPos, pendingTargetDir);
            transitionState = TransitionState::FadingIn;
        }
        return; // Pause player and world movement during fade-out
    } else if (transitionState == TransitionState::FadingIn) {
        transitionAlpha -= TRANSITION_SPEED * deltaTime;
        if (transitionAlpha <= 0.0f) {
            transitionAlpha = 0.0f;
            transitionState = TransitionState::None;
        }
    }

    player.update(deltaTime, tileMap);
    follower.syncWithPlayer(player);
    follower.update(deltaTime, tileMap);

    if (activeEntities) {
        for (auto& entity : *activeEntities) {
            entity->update(deltaTime, tileMap);
        }
    }
}

void OverworldState::render(sf::RenderTarget& target) {
    // 1. Center camera on player with smooth world boundary clamping
    sf::Vector2f cameraCenter = player.getWorldPosition();
    float halfWidth = VIEW_WIDTH / 2.0f;
    float halfHeight = VIEW_HEIGHT / 2.0f;

    float worldWidth = static_cast<float>(tileMap.getWidth() * tileMap.getTileSize());
    float worldHeight = static_cast<float>(tileMap.getHeight() * tileMap.getTileSize());

    if (worldWidth <= VIEW_WIDTH) {
        cameraCenter.x = worldWidth / 2.0f;
    } else {
        cameraCenter.x = std::max(halfWidth, std::min(cameraCenter.x, worldWidth - halfWidth));
    }

    if (worldHeight <= VIEW_HEIGHT) {
        cameraCenter.y = worldHeight / 2.0f;
    } else {
        cameraCenter.y = std::max(halfHeight, std::min(cameraCenter.y, worldHeight - halfHeight));
    }

    gameView.setCenter(cameraCenter);
    target.setView(gameView);

    // 2. Render TileMap
    tileMap.draw(target);

    // 3. Render Entities (Y-sorted for proper depth)
    std::vector<Entity*> renderList;
    renderList.push_back(&player);
    if (follower.isActive()) {
        renderList.push_back(&follower);
    }
    if (activeEntities) {
        for (auto& e : *activeEntities) {
            renderList.push_back(e.get());
        }
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
    if (tileMap.getCurrentMapId() == MapId::OakLab) {
        hudInfo += "   |   Prof. Oak's Research Lab";
    } else if (tileMap.getCurrentMapId() == MapId::PokemonCenter) {
        hudInfo += "   |   Pokemon Center";
    } else if (player.hasStarter()) {
        auto m = player.getFirstAliveMonster();
        if (m) {
            hudInfo += "   |   Partner: " + m->getName() + " (Lv. " + std::to_string(m->getLevel()) + " - HP: " +
                       std::to_string(m->getCurrentHp()) + "/" + std::to_string(m->getMaxHp()) + ")";
        }
    } else {
        hudInfo += "   |   Enter Prof. Oak's Lab (North-West) to get a Starter!";
    }

    sf::Text hintText(resources.getFont(), hudInfo, 14);
    hintText.setFillColor(sf::Color(240, 240, 245, 240));
    hintText.setPosition({15.0f, 6.0f});
    target.draw(hintText);

    // 5. Warp Screen Fade Overlay
    if (transitionAlpha > 0.0f) {
        sf::RectangleShape fadeOverlay({960.0f, 640.0f});
        auto alphaByte = static_cast<std::uint8_t>(std::clamp(transitionAlpha, 0.0f, 255.0f));
        fadeOverlay.setFillColor(sf::Color(0, 0, 0, alphaByte));
        target.draw(fadeOverlay);
    }

    target.setView(worldView); // Restore
}
