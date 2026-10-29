#include "Character.hpp"
#include "TileMap.hpp"
#include <algorithm>

Character::Character(int gridX, int gridY, const sf::Texture& texture, Direction initialFacing)
    : Entity(gridX, gridY),
      facingDirection(initialFacing),
      movementState(MovementState::Idle),
      movementProgress(0.0f),
      movementSpeed(55.0f),
      movementStartPosition(worldPosition),
      sprite(texture),
      animationFrame(0),
      animationTimer(0.0f),
      animationSpeed(0.12f) {
    sprite.setTextureRect(sf::IntRect({0, 0}, {64, 64}));
    sprite.setScale({0.5f, 0.5f});
    sprite.setOrigin({32.0f, 51.0f});
    sprite.setPosition({worldPosition.x + 8.0f, worldPosition.y + 16.0f});
    updateSpriteFrame();
}

void Character::turnTo(Direction dir) {
    if (dir == Direction::None) return;
    facingDirection = dir;
    animationFrame = 0;
    updateSpriteFrame();
}

bool Character::tryStep(Direction dir, const TileMap& tileMap) {
    if (movementState != MovementState::Idle || dir == Direction::None) {
        return false;
    }

    sf::Vector2i offset = directionToOffset(dir);
    sf::Vector2i target = gridPosition + offset;

    if (!tileMap.isWalkable(target.x, target.y)) {
        return false;
    }

    gridPosition = target;
    movementStartPosition = worldPosition;
    movementState = MovementState::Moving;
    movementProgress = 0.0f;
    return true;
}

void Character::update(float deltaTime, const TileMap& /*tileMap*/) {
    if (movementState == MovementState::Moving) {
        updateMovement(deltaTime);
    }
    updateAnimation(deltaTime);
    sprite.setPosition({worldPosition.x + 8.0f, worldPosition.y + 16.0f});
}

void Character::updateMovement(float deltaTime) {
    movementProgress += movementSpeed * deltaTime;

    if (movementProgress >= 16.0f) {
        movementProgress = 16.0f;
        movementState = MovementState::Idle;
    }

    sf::Vector2f targetWorldPosition({
        static_cast<float>(gridPosition.x * 16),
        static_cast<float>(gridPosition.y * 16)
    });

    float progress = movementProgress / 16.0f;
    worldPosition = movementStartPosition + (targetWorldPosition - movementStartPosition) * progress;
}

void Character::updateSpriteFrame() {
    int row = 0;
    switch (facingDirection) {
        case Direction::Down:  row = 0; break;
        case Direction::Up:    row = 1; break;
        case Direction::Right: row = 2; break;
        case Direction::Left:  row = 3; break;
        default:               row = 0; break;
    }

    sprite.setTextureRect(sf::IntRect({animationFrame * 64, row * 64}, {64, 64}));
}

void Character::updateAnimation(float deltaTime) {
    if (movementState != MovementState::Moving) {
        if (animationFrame != 0) {
            animationFrame = 0;
            updateSpriteFrame();
        }
        animationTimer = 0.0f;
        return;
    }

    animationTimer += deltaTime;
    if (animationTimer >= animationSpeed) {
        animationTimer -= animationSpeed;
        animationFrame = (animationFrame + 1) % 4;
        updateSpriteFrame();
    }
}

void Character::draw(sf::RenderTarget& window) {
    window.draw(sprite);
}
