#pragma once
#include "Geode.h"
#include "Block.h"

class GameBlock : public Geode
{
	public:
		/* container array for the blocks in this gameblock */
		Block* shape[3][3];

		/* generate random blocks composing the gameblock around the given center */
		GameBlock(Vector3 center);

		/* delete all of the shapes */
		~GameBlock()
		{
			for(int i = 0; i < 3; ++i)
				for(int j = 0; j < 3; ++j)
					delete shape[i][j];
		}

		/* renderplacemove ALL THE BLOCKS!!! */
		void render();
		void place();
		void moveUp();
		void moveLeft();
		void moveRight();
		void moveDown();
};

