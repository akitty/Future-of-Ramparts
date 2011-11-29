#pragma once
#include "Block.h"


class Player
{
  public:
    // player bounds
    float minX, minZ, maxX, maxZ; 
    // the current block for the player to place
    Block* currentBlock;
    // the starting position
    Vector3 startPos;

    Player();
    ~Player();
};

