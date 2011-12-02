#pragma once
#include "Geode.h"
#include "Block.h"

// numbers that scale the objects (size/scale)
const float WHEEL_RADIUS_SCALE = 0.25f;
const float WHEEL_HEIGHT_SCALE = .25f;
const float CUBE_SCALE = .8333f;
const float CYLINDER_RADIUS_SCALE = .15f;
const float CYLINDER_HEIGHT_SCALE = .8333f;
const float CANNON_SIZE = 4.0f;

const float CYLINDER_HEIGHT = CANNON_SIZE*CYLINDER_HEIGHT_SCALE;
const float CYLINDER_RADIUS = CANNON_SIZE*CYLINDER_RADIUS_SCALE;
const float CYLINDER_YZ_TRANSLATION = sqrt(CYLINDER_HEIGHT/2.0);
const float WHEEL_RADIUS = CANNON_SIZE*WHEEL_RADIUS_SCALE;
const float WHEEL_HEIGHT = CANNON_SIZE*WHEEL_HEIGHT_SCALE;
const float BODY_SIZE = CANNON_SIZE*CUBE_SCALE;
const float CANNONBALL_YZ_TRANSLATION = sqrt(CYLINDER_RADIUS);

const float GRAVITY = -.01;

class Sphere : public Geode
{
  public:
	// position of the center of the sphere
	Vector3 Center;
	// sphere's veloctiy
	Vector3 Velocity;

    Sphere(Vector3 & center = Vector3(0.0, 0.0, 0.0));

	// returns true if the calling sphere collides with the block.
	// the bool is for debugging.
	bool collidesWithBlock(Block &, bool);

	void calcInitialVelocity(Block &);

    void render();
};

