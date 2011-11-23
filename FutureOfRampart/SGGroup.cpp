#include "SGGroup.h"


void SGGroup::draw(Matrix4 & m)
{
  std::list<Node*>::iterator nodes;

  for(nodes = children.begin(); nodes != children.end(); ++nodes)
  {
    (*nodes)->draw(m);
  }
}