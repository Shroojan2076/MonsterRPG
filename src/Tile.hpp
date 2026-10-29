#pragma once

class Tile {
private:
    int id;
    bool walkable;
    bool tallGrass;

public:
    explicit Tile(int id = 0, bool walkable = true, bool tallGrass = false);

    int getId() const;
    bool isWalkable() const;
    bool isTallGrass() const;
};