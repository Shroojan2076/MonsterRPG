#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.hpp"

enum class MapId {
    Overworld,
    OakLab,
    PokemonCenter
};

class TileMap {
public:
    static constexpr int TILE_SIZE = 16;
    static constexpr int OVERWORLD_WIDTH = 44;
    static constexpr int OVERWORLD_HEIGHT = 28;
    static constexpr int INTERIOR_WIDTH = 14;
    static constexpr int INTERIOR_HEIGHT = 11;

private:
    MapId currentMapId;
    int currentWidth;
    int currentHeight;
    std::vector<std::vector<Tile>> tiles;
    const sf::Texture& tilesetTexture;

    void initializeOverworld();
    void initializeOakLab();
    void initializePokemonCenter();

public:
    explicit TileMap(const sf::Texture& tilesetTexture);

    void loadMap(MapId id);
    MapId getCurrentMapId() const { return currentMapId; }

    void draw(sf::RenderTarget& window);
    bool isWalkable(int x, int y) const;
    bool isTallGrass(int x, int y) const;

    int getWidth() const { return currentWidth; }
    int getHeight() const { return currentHeight; }
    int getTileSize() const { return TILE_SIZE; }
};
