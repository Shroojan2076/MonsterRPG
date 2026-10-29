#pragma once

#include <SFML/Graphics.hpp>
#include <string>

enum class Direction {
    None,
    Up,
    Down,
    Left,
    Right
};

enum class MovementState {
    Idle,
    Moving
};

enum class ElementType {
    Normal,
    Fire,
    Water,
    Grass,
    Electric
};

inline sf::Vector2i directionToOffset(Direction dir) {
    switch (dir) {
        case Direction::Up:    return {0, -1};
        case Direction::Down:  return {0, 1};
        case Direction::Left:  return {-1, 0};
        case Direction::Right: return {1, 0};
        default:               return {0, 0};
    }
}
