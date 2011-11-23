#pragma once
#include "SGGroup.h"

class MatrixTransform : public SGGroup
{
  protected:
    Matrix4 transform, rotator;

  public:
    
    // create a matrix transform with the identity
    MatrixTransform() { transform.identity(); }

    // create a matrix transform node with the given input matrix
    MatrixTransform(Matrix4 & m) { transform = m; }

    // set the transformation matrix
    void setTransformation(Matrix4 & m) { transform = m; }

    // set the rotation of this transformation
    void setRotation(Matrix4 & rot);

    // return the transformation matrix
    Matrix4 & getTransformation() { return transform; }

    void draw(Matrix4 & m);
};

