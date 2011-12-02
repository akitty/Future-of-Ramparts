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

void Player::placeGameBlock()
{
	currentBlock->place();
}

void Player::placeCannon()
{

}

void Player::handleInputs(char key)
{
	if(key == keys[PLAYER_KEY_UP])
	{
		if(currentBlock != NULL)
		{
			if(currC + 1 < columns)
			{
				currentBlock->moveUp();
				currPos.z -= BLOCK_SIZE;
				currC++;
			}
		}
	}
	else if(key == keys[PLAYER_KEY_LEFT])
	{
		if(currentBlock != NULL)
		{
			if(currR - 1 >= 0)
			{
				currentBlock->moveLeft();
				currPos.x -= BLOCK_SIZE;
				currR--;
			}
		}
	}
	else if(key == keys[PLAYER_KEY_DOWN])
	{
		if(currentBlock != NULL)
		{
			if(currC - 1 >= 0)
			{
				currentBlock->moveDown();
				currPos.z += BLOCK_SIZE;
				currC--;
			}
		}
	}
	else if(key == keys[PLAYER_KEY_RIGHT])
	{
		if(currentBlock != NULL)
		{
			if(currR + 1 < rows)
			{
				currentBlock->moveRight();
				currPos.x += BLOCK_SIZE;
				currR++;
			}
		}
	}
	else if(key == keys[PLAYER_KEY_ACT])
	{
		if(currentBlock != NULL)
		{
			placeGameBlock();
			region[currR][currC] = currentBlock;
			currentBlock = NULL;
		}
	}
	else if(key == keys[PLAYER_KEY_ROTATE])
	{

	}

	cout << "CURRENT LOCATION: " << "ROW: " << currR << ", COL: " << currC << endl;
}

void Player::calculateScore()
{

}

void Player::giveBlock()
{
	Block* newB = new Block(Vector3(1.0f, 1.0f, 1.0f), BLOCK_TOP, BLOCK_FRONT, BLOCK_BACK, BLOCK_LEFT, BLOCK_RIGHT, BLOCK_RIGHT, true);
	
	// move block to current position
	newB->position = currPos;

	// set the current block pointer for rendering
    currentBlock = newB;
}

// void Player::giveCannon(Cannon* can) {}

void Player::render()
{
	// draw player's blocks
	for(int i = 0; i < rows; ++i)
	{
		for(int j = 0; j < columns; ++j)
		{
			if(region[i][j] != NULL)
				region[i][j]->render();
		}
	}

	// draw current block
	if(currentBlock != NULL)
		currentBlock->render();
}
