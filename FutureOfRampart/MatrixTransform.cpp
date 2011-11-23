#include "MatrixTransform.h"
#include "SGGroup.h"
#include <GL\glut.h>
#include <iostream>

static int counter = 0;

void MatrixTransform::draw(Matrix4 & m)
{
  glPushMatrix();

    std::list<Node*>::iterator nodes;

    Matrix4 tf(m);

    //std::cout << "BEFORE TRANFORM: " << std::endl;

    //tf.printMe();

    tf.multiply(transform);

    // apply any rotations to this transform
    tf.multiply(rotator);

    glMultMatrixf(tf.getPointer());

    //std::cout << "AFTER TRANFORM: " << std::endl;

    //tf.printMe();

    //std::cout << counter++ << std::endl << std::endl;

    for(nodes = children.begin(); nodes != children.end(); ++nodes)
    {
      (*nodes)->draw(tf);
      glPopMatrix();
    }
}

void MatrixTransform::setRotation(Matrix4 & rot)
{
  rotator = rot;
}
