#pragma once
#include "Geode.h"

class Sphere : public Geode
{
  protected:
    Vector3 Color, Params, Scale;
    bool scaled; 
    bool Wire;

  public:
    Sphere();

    Sphere(Vector3 & params, Vector3 & color, Vector3 & scale = Vector3(1.0,1.0,1.0), bool wire = false);

    void render();
};

