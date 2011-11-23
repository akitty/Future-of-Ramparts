#pragma once
#include "Node.h"

class Geode : public Node
{

  public:
    //Geode();

    // draw the subclass of this Geode
    void draw(Matrix4 & m);

    // render the object class on screen - must be overwritten
    virtual void render() = 0;
};

