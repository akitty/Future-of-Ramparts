#pragma once
#include "Node.h"
#include "SGGroup.h"
#include "Block.h"

const int MAP_SIZE = 10;

/**
 * The map containing the base world, each player's
 * blocks, and the delimiting zones
 */
class Map : public Node
{
  public:
    // the groups containing the objects for player1 and player2
    SGGroup player1, player2;
    // the base world grid
    Block base[MAP_SIZE][MAP_SIZE];

    Map();

    void draw(Matrix4 &m);
};

