#pragma once
#include "geode.h"
#include <GL/glut.h>

// numbers that scale the objects (size/scale)
const float SPHERE_SCALE = 4.0f;
const float CUBE_SCALE = 1.2f;
const float CYLINDER_RADIUS = 4.0f;
const float CYLINDER_HEIGHT = 1.2f;


class Cannon : public Geode
{
  protected:
    Vector3 Color;
	float Size;

  public:
	// position of the center of the cannon
	Vector3 Center;

    Cannon();

	Cannon(Vector3 color, float size = 4.0, Vector3 center = Vector3(0,0,0));

    void render();
};

