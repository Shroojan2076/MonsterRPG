#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.hpp"

class TileMap {
public:
    static constexpr int TILE_SIZE = 16;
    static constexpr int MAP_WIDTH = 44;
    static constexpr int MAP_HEIGHT = 28;

private:
    std::vector<std::vector<Tile>> tiles;
    const sf::Texture& tilesetTexture;

    void initializeMap();

public:
    explicit TileMap(const sf::Texture& tilesetTexture);

    void draw(sf::RenderTarget& window);
    bool isWalkable(int x, int y) const;
    bool isTallGrass(int x, int y) const;

    int getWidth() const;
    int getHeight() const;
    int getTileSize() const;
};