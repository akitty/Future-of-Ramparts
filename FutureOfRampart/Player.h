#pragma once
#include "Block.h"
#include "Geode.h"
#include "Explosion.h"


class Player : public Geode
{
  public:
    // player bounds
    float minX, minZ, maxX, maxZ; 
    // the current block for the player to place
    Block* currentBlock;
    // the starting position
    Vector3 origin;
    vector<Block*> blocks;
    vector<Explosion*> explosions;

    Player(Vector3 o) : origin(o){}
    ~Player();

    void render();

    void detonate();
};

