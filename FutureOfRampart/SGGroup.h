#pragma once
#include <list>
#include "Node.h"

class SGGroup : public Node
{
  public:

    // add a child to this group
    void addChild(Node* child) { children.push_back(child); }

    // remove a child from this group
    void removeChild(Node* child) { children.remove(child); }

    void removeChildren() { children.clear(); }
    int numChildren() { return children.size(); }

    // draw all subchildren, passing them the given model matrix
    void draw(Matrix4 & m);

  protected:

    std::list<Node*> children;
};

