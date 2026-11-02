#include "TileMap.hpp"

TileMap::TileMap(const sf::Texture& tilesetTexture)
    : currentMapId(MapId::Overworld),
      currentWidth(OVERWORLD_WIDTH),
      currentHeight(OVERWORLD_HEIGHT),
      tilesetTexture(tilesetTexture) {
    loadMap(MapId::Overworld);
}

void TileMap::loadMap(MapId id) {
    currentMapId = id;
    switch (id) {
        case MapId::Overworld:
            initializeOverworld();
            break;
        case MapId::OakLab:
            initializeOakLab();
            break;
        case MapId::PokemonCenter:
            initializePokemonCenter();
            break;
    }
}

void TileMap::initializeOverworld() {
    currentWidth = OVERWORLD_WIDTH;
    currentHeight = OVERWORLD_HEIGHT;
    tiles.assign(currentHeight, std::vector<Tile>(currentWidth, Tile(0, true, false)));

    // Outer Boundary: Directional wooden fences with proper corners
    for (int x = 0; x < currentWidth; ++x) {
        tiles[0][x] = Tile(6, false, false);                 // Top Horizontal Fence
        tiles[currentHeight - 1][x] = Tile(6, false, false); // Bottom Horizontal Fence
    }
    for (int y = 0; y < currentHeight; ++y) {
        tiles[y][0] = Tile(7, false, false);                // Left Vertical Fence
        tiles[y][currentWidth - 1] = Tile(7, false, false); // Right Vertical Fence
    }

    // 4 Corner fence posts
    tiles[0][0] = Tile(8, false, false);                                  // Top-Left Corner
    tiles[0][currentWidth - 1] = Tile(9, false, false);                   // Top-Right Corner
    tiles[currentHeight - 1][0] = Tile(10, false, false);                 // Bottom-Left Corner
    tiles[currentHeight - 1][currentWidth - 1] = Tile(11, false, false);  // Bottom-Right Corner

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
    tiles[0][20] = Tile(14, false, false);                 // Top T-Junction
    tiles[currentHeight - 1][20] = Tile(14, false, false); // Bottom T-Junction

    for (int y = 1; y < currentHeight - 1; ++y) {
        if (y == 11) {
            tiles[y][20] = Tile(12, false, false); // Top gate post
        } else if (y == 14) {
            tiles[y][20] = Tile(13, false, false); // Bottom gate post
        } else if (y != 12 && y != 13) {
            tiles[y][20] = Tile(7, false, false);  // Vertical fence
        }
    }

    // Decorative Flowers & Lamp Posts in Town
    tiles[11][9] = Tile(23, false, false);  // Lamp post north
    tiles[14][9] = Tile(23, false, false);  // Lamp post south
    tiles[11][12] = Tile(23, false, false);
    tiles[14][12] = Tile(23, false, false);

    tiles[10][6] = Tile(4, true, false);  // Red flowers
    tiles[10][7] = Tile(5, true, false);  // Yellow flowers
    tiles[15][6] = Tile(5, true, false);  // Yellow flowers
    tiles[15][7] = Tile(15, true, false); // Blue flowers

    // BUILDING 1: Professor Oak's Research Lab (Blue Roof) at cols 4..8, rows 3..7
    // Authentic 5x5 building tiles (IDs 24 to 48)
    for (int r = 0; r < 5; ++r) {
        for (int c = 0; c < 5; ++c) {
            int tileId = 24 + (r * 5 + c);
            bool walkable = (r == 4 && c == 2); // Front entrance door at (6, 7)
            tiles[3 + r][4 + c] = Tile(tileId, walkable, false);
        }
    }

    // BUILDING 2: Pokémon Clinic / Center (Red Roof) at cols 4..8, rows 14..18
    // Authentic 5x5 building tiles (IDs 49 to 73)
    for (int r = 0; r < 5; ++r) {
        for (int c = 0; c < 5; ++c) {
            int tileId = 49 + (r * 5 + c);
            bool walkable = (r == 4 && c == 2); // Clinic entrance door at (6, 18)
            tiles[14 + r][4 + c] = Tile(tileId, walkable, false);
        }
    }

    // Town Signpost
    tiles[11][14] = Tile(17, false, false);

    // ==========================================
    // 2. EAST SIDE: WHISPERING WOODS (Cols 21 to 43)
    // ==========================================
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
        if (rx >= 0 && rx + 1 < currentWidth && ry >= 0 && ry + 1 < currentHeight) {
            tiles[ry][rx]         = Tile(19, false, false); // Tree Top Left
            tiles[ry][rx + 1]     = Tile(20, false, false); // Tree Top Right
            tiles[ry + 1][rx]     = Tile(21, false, false); // Trunk Left
            tiles[ry + 1][rx + 1] = Tile(22, false, false); // Trunk Right
        }
    };

    // Dense Forest perimeter & groves
    for (int x = 21; x < currentWidth - 2; x += 2) {
        placeTree(x, 1);
        placeTree(x, currentHeight - 3);
    }
    for (int y = 2; y < currentHeight - 3; y += 2) {
        placeTree(currentWidth - 3, y);
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

    // Ground under Item Ball in South-East grove
    tiles[22][38] = Tile(0, true, false);
}

void TileMap::initializeOakLab() {
    currentWidth = INTERIOR_WIDTH;
    currentHeight = INTERIOR_HEIGHT;
    tiles.assign(currentHeight, std::vector<Tile>(currentWidth, Tile(80, false, false))); // Default Void

    // Layout array (14 columns x 11 rows)
    const int layout[11][14] = {
        // Row 0: Void
        {80, 80,  80,  80,  80,  80,  80,  80,  80,  80,  80,  80,  80, 80},
        // Row 1: Top Wall Upper & Bookshelves Top & Whiteboard Top
        {80, 84,  88, 109,  88,  90,  90,  84,  88, 109,  88,  84,  80, 80},
        // Row 2: Top Wall Lower & Bookshelves Bottom & Whiteboard Bottom
        {80, 85,  89, 110,  89,  91,  91,  85,  89, 110,  89,  85,  80, 80},
        // Row 3: Oak's Workstation Row (Computer at 4, Microscope at 8, Oak stands at 6, 3)
        {80, 74,  81,  81,  92,  81,  81,  81, 111,  81,  81,  75,  80, 80},
        // Row 4: Research Table across cols 5..7 (Desk L, Starter Tray, Desk R)
        {80, 74,  81,  81,  81,  94,  93,  96,  81,  81,  81,  75,  80, 80},
        // Row 5: Open Aisle (Player stands at 6, 5 facing Up to talk to Oak)
        {80, 74,  81,  81,  81,  81,  81,  81,  81,  81,  81,  75,  80, 80},
        // Row 6: Side Library Bookshelves Top
        {80, 74,  88, 109,  81,  81,  81,  81,  81,  88, 109,  75,  80, 80},
        // Row 7: Side Library Bookshelves Bottom
        {80, 74,  89, 110,  81,  81,  81,  81,  81,  89, 110,  75,  80, 80},
        // Row 8: Plants & Entrance Approach (Player spawns at 6, 8 facing Up)
        {80, 74, 106,  81,  81,  81,  81,  81,  81,  81, 106,  75,  80, 80},
        // Row 9: Bottom Wall with Wooden Exit Mat at Col 6
        {80, 78,  78,  78,  78,  78,  97,  78,  78,  78,  78,  78,  80, 80},
        // Row 10: Void
        {80, 80,  80,  80,  80,  80,  80,  80,  80,  80,  80,  80,  80, 80}
    };

    for (int y = 0; y < currentHeight; ++y) {
        for (int x = 0; x < currentWidth; ++x) {
            int tid = layout[y][x];
            // Walkable: Sandstone Floor (81) and Exit Mat (97)
            bool walkable = (tid == 81 || tid == 97);
            tiles[y][x] = Tile(tid, walkable, false);
        }
    }
}

void TileMap::initializePokemonCenter() {
    currentWidth = INTERIOR_WIDTH;
    currentHeight = INTERIOR_HEIGHT;
    tiles.assign(currentHeight, std::vector<Tile>(currentWidth, Tile(80, false, false))); // Default Void

    // Layout array (14 columns x 11 rows)
    const int layout[11][14] = {
        // Row 0: Void
        {80, 80,  80,  80,  80,  80,  80,  80,  80,  80,  80,  80,  80, 80},
        // Row 1: Clinic Upper Wall
        {80, 86,  86,  86,  86,  86,  86,  86,  86,  86,  86,  86,  80, 80},
        // Row 2: Clinic Lower Wall, Mounted Healing Machine at col 6, Trainer PC at col 10
        {80, 87, 107,  87,  87,  87, 101,  87,  87,  87, 102,  87,  80, 80},
        // Row 3: Nurse Joy Station (Nurse Joy stands at 6, 3 facing Down)
        {80, 76,  82,  82,  82,  82,  82,  82,  82,  82,  82,  77,  80, 80},
        // Row 4: Service Counter across cols 5..7 (Counter L, Counter C, Counter R), Vending Machine at col 2
        {80, 76, 103,  82,  82,  98, 100,  99,  82,  82,  82,  77,  80, 80},
        // Row 5: Aisle with Red Carpet runner (Player stands at 6, 5 facing Up to talk to Nurse Joy)
        {80, 76,  82,  82,  82,  82,  83,  82,  82,  82,  82,  77,  80, 80},
        // Row 6: Waiting Area (Waiting Bench at cols 2,3, Carpet at col 6)
        {80, 76, 104, 105,  82,  82,  83,  82,  82,  82,  82,  77,  80, 80},
        // Row 7: Checkered Floor & Red Carpet
        {80, 76,  82,  82,  82,  82,  83,  82,  82,  82,  82,  77,  80, 80},
        // Row 8: Plants & Red Carpet (Player spawns at 6, 8 facing Up)
        {80, 76, 107,  82,  82,  82,  83,  82,  82,  82, 107,  77,  80, 80},
        // Row 9: Bottom Wall with Clinic Red Exit Welcome Mat at Col 6
        {80, 79,  79,  79,  79,  79, 108,  79,  79,  79,  79,  79,  80, 80},
        // Row 10: Void
        {80, 80,  80,  80,  80,  80,  80,  80,  80,  80,  80,  80,  80, 80}
    };

    for (int y = 0; y < currentHeight; ++y) {
        for (int x = 0; x < currentWidth; ++x) {
            int tid = layout[y][x];
            // Walkable: Checkered Floor (82), Red Carpet (83), Exit Mat (108)
            bool walkable = (tid == 82 || tid == 83 || tid == 108);
            tiles[y][x] = Tile(tid, walkable, false);
        }
    }
}

void TileMap::draw(sf::RenderTarget& window) {
    sf::Sprite sprite(tilesetTexture);
    sprite.setScale({0.5f, 0.5f}); // 32x32 tiles scaled to 16x16 world units

    for (int y = 0; y < currentHeight; ++y) {
        for (int x = 0; x < currentWidth; ++x) {
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
    if (x < 0 || x >= currentWidth || y < 0 || y >= currentHeight) {
        return false;
    }
    return tiles[y][x].isWalkable();
}

bool TileMap::isTallGrass(int x, int y) const {
    if (x < 0 || x >= currentWidth || y < 0 || y >= currentHeight) {
        return false;
    }
    return tiles[y][x].isTallGrass();
}
