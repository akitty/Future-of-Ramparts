#pragma once
//#include "geode.h"
#include "Sphere.h"

// offsets to center the cannon on a grid square
const float XOFFSET = 0.0;
const float YOFFSET = WHEEL_RADIUS;
const float ZOFFSET = -18.0f;

class Cannon : public Geode
{
  public:
	// position of the center of the cannon, useful for bounding box around cannon if necessary
	Vector3 Center;
	// initial position of cannonball when firing 
	Vector3 CannonballInitialCenter;

	// the center parameter represents the corner of the grid space (make sure which corner)
	// need to figure out how to perfectly center the cannon with the grid
	// can easily force the x space to be 4, we know all the values that determine it, the other components don't need to be modified
	Cannon(Vector3 center = Vector3(0.0,0.0,0.0));

	// return a sphere with its center as the initial position
	Sphere fire();

    void render();
};

