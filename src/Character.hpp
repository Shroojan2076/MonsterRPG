#pragma once

#include "Entity.hpp"

// Intermediate Abstract Class for moving humanoid/creature actors (Inherits from Entity)
class Character : public Entity {
protected:
    Direction facingDirection;
    MovementState movementState;

    float movementProgress;
    float movementSpeed;
    sf::Vector2f movementStartPosition;

    sf::Sprite sprite;
    int animationFrame;
    float animationTimer;
    float animationSpeed;

    void updateMovement(float deltaTime);
    void updateAnimation(float deltaTime);
    virtual void updateSpriteFrame();

public:
    Character(int gridX, int gridY, const sf::Texture& texture, Direction initialFacing = Direction::Down);

    void turnTo(Direction dir);
    bool tryStep(Direction dir, const TileMap& tileMap);

    void update(float deltaTime, const TileMap& tileMap) override;
    void draw(sf::RenderTarget& window) override;

    Direction getFacingDirection() const { return facingDirection; }
    MovementState getMovementState() const { return movementState; }
    bool isMoving() const { return movementState == MovementState::Moving; }
};
