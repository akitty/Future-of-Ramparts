#pragma once
#include "Geode.h"
#include "Block.h"

class Sphere : public Geode
{
  protected:
    Vector3 Color, Params, Scale;
    bool scaled; 
    bool Wire;

  public:
	// position of the center of the sphere
	Vector3 Center;
	// sphere's veloctiy
	Vector3 Velocity;

    Sphere();

    Sphere(Vector3 & params, Vector3 & color, Vector3 & center = Vector3(0.0, 0.0, 0.0), Vector3 & velocity = Vector3(0.0, 0.0, 0.0), Vector3 & scale = Vector3(1.0,1.0,1.0), bool wire = false);

	// returns true if the calling sphere collides with the block.
	// the bool is for debugging.
	bool collidesWithBlock(Block &, bool);

    void render();
};

