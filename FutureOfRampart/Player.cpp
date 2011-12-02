#include "Player.h"

Player::~Player()
{
	if(currentBlock != NULL)
		delete currentBlock;
	// destructor for the region
	if(region != NULL)
	{
		// delete all of the geode pointers
		for(int i = 0; i < rows; ++i)
		{
			for(int j = 0; j < columns; ++j)
			{
				delete region[i][j];
			}
		}	
			
		// delete all of the column pointers
		for(int i = 0; i < rows; ++i)
			delete[] region[i];
			
		// delete the row pointer
		delete[] region;
	}
}

void Player::render()
{
}
