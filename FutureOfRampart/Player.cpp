#include "Player.h"

Player::~Player()
{
}

void Player::render()
{
  for(int i = 0; i < blocks.size(); ++i)
  {
    blocks.at(i)->render();
  }
}
