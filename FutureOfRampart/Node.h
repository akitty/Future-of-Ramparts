#pragma once
#include "Matrix4.h"

class Node
{

  public:

    virtual void draw(Matrix4 & m) = 0;
};
