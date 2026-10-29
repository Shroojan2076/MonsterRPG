#include "Tile.hpp"

Tile::Tile(int id, bool walkable, bool tallGrass)
    : id(id), walkable(walkable), tallGrass(tallGrass) {}

int Tile::getId() const { return id; }
bool Tile::isWalkable() const { return walkable; }
bool Tile::isTallGrass() const { return tallGrass; }