#include "Player.hpp"
#include "TileMap.hpp"

Player::Player(int gridX, int gridY, const sf::Texture& walkTex, const sf::Texture& runTex)
    : Character(gridX, gridY, walkTex, Direction::Down),
      walkTexture(walkTex),
      runTexture(runTex),
      isRunning(false),
      hasStarterMonster(false),
      defeatedBoss(false),
      turnCooldownTimer(0.0f),
      lastPressedDirection(Direction::None),
      previousGridPosition({gridX, gridY}) {
    // Initial basic inventory items for adventuring
    inventory.addItem(std::make_shared<PotionItem>(20), 3);
    inventory.addItem(std::make_shared<CaptureBallItem>(1.0f), 5);
}

void Player::update(float deltaTime, const TileMap& tileMap) {
    MovementState previousState = movementState;

    if (turnCooldownTimer > 0.0f) {
        turnCooldownTimer -= deltaTime;
    }

    if (movementState == MovementState::Idle) {
        handleInput(tileMap);
    }

    Character::update(deltaTime, tileMap);

    // Step completed trigger (stepped into new tile)
    if (previousState == MovementState::Moving && movementState == MovementState::Idle) {
        if (onStepCompleted) {
            onStepCompleted(gridPosition);
        }
    }
}

void Player::handleInput(const TileMap& tileMap) {
    // Sprint / Running shoes check
    bool shiftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) ||
                        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift);

    if (shiftPressed != isRunning) {
        isRunning = shiftPressed;
        if (isRunning) {
            movementSpeed = 120.0f; // Over 2x speed for rapid exploration
            animationSpeed = 0.07f;
            sprite.setTexture(runTexture, false);
        } else {
            movementSpeed = 55.0f;
            animationSpeed = 0.12f;
            sprite.setTexture(walkTexture, false);
        }
        updateSpriteFrame();
    }

    Direction inputDir = Direction::None;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        inputDir = Direction::Up;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        inputDir = Direction::Down;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        inputDir = Direction::Left;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        inputDir = Direction::Right;
    }

    if (inputDir == Direction::None) {
        lastPressedDirection = Direction::None;
        return;
    }

    // Goal #1: Turn in place first with standing animation frame
    if (inputDir != facingDirection) {
        turnTo(inputDir);
        turnCooldownTimer = 0.14f; // Buffer delay so tap turns in place, hold continues forward
        lastPressedDirection = inputDir;
        return;
    }

    // If facing the same direction and turn cooldown has elapsed, move to next tile!
    if (turnCooldownTimer <= 0.0f) {
        sf::Vector2i target = gridPosition + directionToOffset(inputDir);

        // Solid entity collision check: cannot walk through NPCs, signs, or obstacles
        if (collisionCheck && collisionCheck(target.x, target.y)) {
            return;
        }

        previousGridPosition = gridPosition;
        tryStep(inputDir, tileMap);
    }
}

sf::Vector2i Player::getFrontTile() const {
    return gridPosition + directionToOffset(facingDirection);
}

void Player::addMonster(const std::shared_ptr<Monster>& monster) {
    if (monster && party.size() < 6) {
        party.push_back(monster);
    }
}

std::vector<std::shared_ptr<Monster>>& Player::getParty() { return party; }
const std::vector<std::shared_ptr<Monster>>& Player::getParty() const { return party; }

std::shared_ptr<Monster> Player::getFirstAliveMonster() {
    for (auto& m : party) {
        if (!m->isFainted()) {
            return m;
        }
    }
    return nullptr;
}

void Player::healAllMonsters() {
    for (auto& m : party) {
        m->fullHeal();
    }
}

Inventory& Player::getInventory() { return inventory; }
const Inventory& Player::getInventory() const { return inventory; }

bool Player::hasStarter() const { return hasStarterMonster; }
void Player::setHasStarter(bool val) { hasStarterMonster = val; }

bool Player::isBossDefeated() const { return defeatedBoss; }
void Player::setBossDefeated(bool val) { defeatedBoss = val; }

void Player::setOnStepCompleted(std::function<void(sf::Vector2i)> callback) {
    onStepCompleted = std::move(callback);
}

void Player::setCollisionCallback(std::function<bool(int, int)> callback) {
    collisionCheck = std::move(callback);
}