#include "TileMap.hpp"

TileMap::TileMap(const sf::Texture& tilesetTexture)
    : tilesetTexture(tilesetTexture) {
    initializeMap();
}

void TileMap::initializeMap() {
    tiles.resize(MAP_HEIGHT, std::vector<Tile>(MAP_WIDTH, Tile(0, true, false)));

    // Outer Boundary: dense trees or stone fences
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            if (x == 0 || y == 0 || y == MAP_HEIGHT - 1 || x == MAP_WIDTH - 1) {
                tiles[y][x] = Tile(6, false, false); // Wooden Fence / Border
            }
        }
    }

    // ==========================================
    // 1. WEST SIDE: OAKDALE TOWN (Cols 1 to 20)
    // ==========================================

    // Town Main Square & Roads
    for (int y = 3; y < 25; ++y) {
        tiles[y][10] = Tile(1, true, false); // North-South Main Cobblestone Avenue
        tiles[y][11] = Tile(1, true, false);
    }
    for (int x = 2; x < 21; ++x) {
        tiles[12][x] = Tile(1, true, false); // East-West Main Street
        tiles[13][x] = Tile(1, true, false);
    }

    // Secondary paths
    for (int x = 3; x <= 9; ++x) {
        tiles[8][x] = Tile(1, true, false);  // Path in front of Lab
        tiles[19][x] = Tile(1, true, false); // Path in front of Clinic
    }

    // Town dividing fence along col 20 (with gateway opening at rows 12 & 13)
    for (int y = 1; y < MAP_HEIGHT - 1; ++y) {
        if (y != 12 && y != 13) {
            tiles[y][20] = Tile(6, false, false);
        }
    }

    // Decorative Flowers & Lamp Posts in Town
    tiles[11][9] = Tile(23, false, false);  // Lamp post north
    tiles[14][9] = Tile(23, false, false);  // Lamp post south
    tiles[11][12] = Tile(23, false, false);
    tiles[14][12] = Tile(23, false, false);

    tiles[10][6] = Tile(4, true, false); // Red flowers
    tiles[10][7] = Tile(5, true, false); // Yellow flowers
    tiles[15][6] = Tile(5, true, false);
    tiles[15][7] = Tile(4, true, false);

    // BUILDING 1: Professor Oak's Research Lab (Blue Roof) at cols 4..8, rows 3..7
    // Roof (row 3, 4)
    tiles[3][4] = Tile(11, false, false);
    tiles[3][5] = Tile(12, false, false);
    tiles[3][6] = Tile(12, false, false);
    tiles[3][7] = Tile(12, false, false);
    tiles[3][8] = Tile(13, false, false);

    tiles[4][4] = Tile(11, false, false);
    tiles[4][5] = Tile(12, false, false);
    tiles[4][6] = Tile(12, false, false);
    tiles[4][7] = Tile(12, false, false);
    tiles[4][8] = Tile(13, false, false);

    // Walls & Door (row 5, 6, 7)
    for (int r = 5; r <= 7; ++r) {
        for (int c = 4; c <= 8; ++c) {
            tiles[r][c] = Tile(14, false, false);
        }
    }
    tiles[6][5] = Tile(16, false, false); // Window
    tiles[6][7] = Tile(16, false, false); // Window
    tiles[7][6] = Tile(15, true, false);  // Front Entrance Door

    // BUILDING 2: Pokémon Clinic / Center (Red Roof) at cols 4..8, rows 14..18
    tiles[14][4] = Tile(8, false, false);
    tiles[14][5] = Tile(9, false, false);
    tiles[14][6] = Tile(9, false, false);
    tiles[14][7] = Tile(9, false, false);
    tiles[14][8] = Tile(10, false, false);

    tiles[15][4] = Tile(8, false, false);
    tiles[15][5] = Tile(9, false, false);
    tiles[15][6] = Tile(9, false, false);
    tiles[15][7] = Tile(9, false, false);
    tiles[15][8] = Tile(10, false, false);

    for (int r = 16; r <= 18; ++r) {
        for (int c = 4; c <= 8; ++c) {
            tiles[r][c] = Tile(14, false, false);
        }
    }
    tiles[17][5] = Tile(16, false, false); // Window
    tiles[17][7] = Tile(16, false, false); // Window
    tiles[18][6] = Tile(15, true, false);  // Clinic Door

    // Town Signpost
    tiles[11][14] = Tile(17, false, false);

    for (int x = 21; x <= 34; ++x) {
        tiles[12][x] = Tile(2, true, false);
        tiles[13][x] = Tile(2, true, false);
    }
    // Trail branching North to Boss Clearing
    for (int y = 5; y <= 12; ++y) {
        tiles[y][33] = Tile(2, true, false);
        tiles[y][34] = Tile(2, true, false);
    }
    for (int x = 34; x <= 39; ++x) {
        tiles[5][x] = Tile(2, true, false);
        tiles[6][x] = Tile(2, true, false);
    }

    // Trail branching South to Secluded Grove
    for (int y = 13; y <= 22; ++y) {
        tiles[y][27] = Tile(2, true, false);
        tiles[y][28] = Tile(2, true, false);
    }
    for (int x = 28; x <= 38; ++x) {
        tiles[22][x] = Tile(2, true, false);
    }

    // Helper lambda to place 2x2 Trees
    auto placeTree = [&](int rx, int ry) {
        if (rx >= 0 && rx + 1 < MAP_WIDTH && ry >= 0 && ry + 1 < MAP_HEIGHT) {
            tiles[ry][rx]         = Tile(19, false, false); // Tree Top Left
            tiles[ry][rx + 1]     = Tile(20, false, false); // Tree Top Right
            tiles[ry + 1][rx]     = Tile(21, false, false); // Trunk Left
            tiles[ry + 1][rx + 1] = Tile(22, false, false); // Trunk Right
        }
    };

    // Dense Forest perimeter & groves
    for (int x = 21; x < MAP_WIDTH - 2; x += 2) {
        placeTree(x, 1);
        placeTree(x, MAP_HEIGHT - 3);
    }
    for (int y = 2; y < MAP_HEIGHT - 3; y += 2) {
        placeTree(MAP_WIDTH - 3, y);
    }

    // Internal tree groves dividing the paths
    placeTree(23, 4);
    placeTree(26, 4);
    placeTree(29, 4);

    placeTree(23, 7);
    placeTree(26, 7);
    placeTree(29, 7);

    placeTree(23, 16);
    placeTree(23, 19);
    placeTree(31, 15);
    placeTree(34, 15);
    placeTree(31, 18);
    placeTree(34, 18);

    // ==========================================
    // 3. TALL GRASS PATCHES (Tile 3 - Encounters)
    // ==========================================
    // North grass patch
    for (int y = 9; y <= 11; ++y) {
        for (int x = 23; x <= 28; ++x) {
            tiles[y][x] = Tile(3, true, true);
        }
    }

    // South clearing grass patch
    for (int y = 16; y <= 20; ++y) {
        for (int x = 25; x <= 29; ++x) {
            if (tiles[y][x].isWalkable()) {
                tiles[y][x] = Tile(3, true, true);
            }
        }
    }

    // East boss approach grass patch
    for (int y = 8; y <= 11; ++y) {
        for (int x = 36; x <= 40; ++x) {
            tiles[y][x] = Tile(3, true, true);
        }
    }

    // Forest Signpost at entrance
    tiles[11][22] = Tile(17, false, false);

    // Hidden Item Ball in South-East grove
    tiles[22][38] = Tile(18, true, false);
}

void TileMap::draw(sf::RenderTarget& window) {
    sf::Sprite sprite(tilesetTexture);
    sprite.setScale({0.5f, 0.5f}); // 32x32 tiles scaled to 16x16 world units

    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            int tileId = tiles[y][x].getId();
            int srcX = (tileId % 8) * 32;
            int srcY = (tileId / 8) * 32;

            sprite.setTextureRect(sf::IntRect({srcX, srcY}, {32, 32}));
            sprite.setPosition({
                static_cast<float>(x * TILE_SIZE),
                static_cast<float>(y * TILE_SIZE)
            });

            window.draw(sprite);
        }
    }
}

bool TileMap::isWalkable(int x, int y) const {
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
        return false;
    }
    return tiles[y][x].isWalkable();
}

bool TileMap::isTallGrass(int x, int y) const {
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
        return false;
    }
    return tiles[y][x].isTallGrass();
}

int TileMap::getWidth() const { return MAP_WIDTH; }
int TileMap::getHeight() const { return MAP_HEIGHT; }
int TileMap::getTileSize() const { return TILE_SIZE; }