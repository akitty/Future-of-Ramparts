#pragma once
#include "Node.h"
#include "SGGroup.h"
#include "Block.h"
#include "Sphere.h"
#include "Cannon.h"

const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 48;

/**
 * The map containing the base world, each player's
 * blocks, and the delimiting zones
 */
class Map : public Node
{
  public:
    // the groups containing the objects for player1 and player2
    SGGroup player1, player2;
    
    bool drawn;
    GLuint GAME_MAP;

    // the base world grid
    Block base[MAP_HEIGHT][MAP_WIDTH];

    Map(GLuint textureNums[]);

    void draw(Matrix4 &m);
};

