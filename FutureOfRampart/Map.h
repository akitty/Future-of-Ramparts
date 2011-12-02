#pragma once
#include "Node.h"
#include "SGGroup.h"
#include "Block.h"
#include "Sphere.h"
#include "Cannon.h"

const int MAP_WIDTH = 26;
const int MAP_HEIGHT = 52;

/**
 * The map containing the base world, each player's
 * blocks, and the delimiting zones
 */
class Map : public SGGroup
{
public:
	typedef SGGroup super;

    bool drawn;
    GLuint GAME_MAP;

    // the base world grid
    Block base[MAP_HEIGHT][MAP_WIDTH];

    Map(GLuint textureNums[]);

    void draw(Matrix4 &m);
};

