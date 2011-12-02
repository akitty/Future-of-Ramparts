#pragma once
#include "Block.h"
#include "Cannon.h"
#include "Explosion.h"
#include "Nexus.h"
#include <vector>

// player keys for processing input
const int NUM_KEYS = 7;
const int PLAYER_KEY_UP = 0;
const int PLAYER_KEY_DOWN = 1;
const int PLAYER_KEY_LEFT = 2;
const int PLAYER_KEY_RIGHT = 3;
const int PLAYER_KEY_ACT = 4;
const int PLAYER_KEY_GIVE = 5;
const int PLAYER_KEY_DETONATE = 6;

class Player : public Geode
{
  public:
    // player region bounds
    float minX, 
		  minZ, 
		  maxX, 
		  maxZ; 
    // the cursor pointer for the current block
    Block* currentBlock;
	// this player's nexus
	Nexus* nexus;
    // the starting position - also the position for the fortress to be put up
	Vector3 center;
	// this player's input control keys
	char keys[7];
	// a pointer to the 2 dimensional array of the player's blocks,
	// which are themselves abstract to any kind of "block"
	Geode*** region;
	// helper values
	int rows, columns, spaces;
	// player's emblem texture which gets placed on all of the player's tiles in enclosed portions
	GLuint emblem;
	// current position of the player
	Vector3 currPos;
	// current row and column 
	int currR, currC;
	// maximum bounds in the form of integers
	int minR, maxR, minC, maxC;
	// negative offset for our currR and currC
	int negX, negZ;

	/* 
	 * Initialize this player. 
	 * The origin is the destination of the fortress as well as the cursor starting position.
	 * The key commands are an abstraction of how this player's input is represented.
	 * The bounds are the restrictions on which section of the map this player can place blocks on.
	 * The emblem is the texture put in on enclosed portions of the player's region.
	 */
    Player(int centerXoffset, int centerZoffset, float xmin, float xmax, float zmin, float zmax, char keycommands[], GLuint e) : minX(xmin), maxX(xmax), minZ(zmin), maxZ(zmax), emblem(e)
	{
		// set in key commands
		for(int i = 0; i < NUM_KEYS; ++i)
			keys[i] = keycommands[i];

		// create the dimensions of the region
		rows = ((maxX - minX) / BLOCK_SIZE);
		columns = ((maxZ - minZ) / BLOCK_SIZE);
		
		// should not actually be shrinking these....
		spaces = rows * columns;
		
		cout << "ROWS: " << rows << endl;
		cout << "MINIMUM ROW: " << minR << endl;
		cout << "MAXIMUM ROW: " << maxR << endl;
		cout << "MINIMUM COLUMN "  << minC << endl;
		cout << "MAXIMUM COLUMN " << maxC << endl;
		cout << "COLUMNS: " << columns << endl;

		// initialize the region's dimensions
		region = new Geode**[rows];
		for(int i = 0; i < rows; ++i)
		{
			region[i] = new Geode*[columns];
		}

		// initialize the pointers in the region to null
		for(int i = 0; i < rows; ++i)
		{
			for(int j = 0; j < columns; ++j)
			{
				region[i][j] = NULL;
			}
		}

		// initialize pointers to null
		currentBlock = NULL;

		// we want to calculate and place the fortress at the center location

		// start the position for the first block to be given at
		// needs to be the minimum values of x and z (actual) + the offset in each direction
		center = Vector3(minX + BLOCK_SIZE * centerXoffset, 
						 BLOCK_SIZE, 
						 minZ + BLOCK_SIZE * centerZoffset);

		currPos = Vector3(center.x, center.y + BLOCK_SIZE, center.z);

		// the current position just needs to be that offset
		currR = centerXoffset;
		currC = centerZoffset;

		nexus = new Nexus(currPos, BLOCK_FRONT, BLOCK_BACK, e);
		region[currR][currC] = nexus;
	}

	/* 
	 * Free all the resources allocated with this player.
	 */
    ~Player();

	/* 
	 * Checks collisions and tries to place the current block. 
	 * If the block forms an enclosed structure, call the 
	 * completeEnclosedRegion() function.
	 */
	void placeGameBlock();

	/*
	 * Draw all of the player's objects that are currently on screen.
	 * Draw the current block. 
	 * //LATER// Draw the score, player name, and upcoming block view. 
	 */
    void render();

	/*
	 * Handle the player's input.
	 */
	Geode* handleInputs(char key);

	/*
	 * Calculate this player's score based on the number of emblem textures and cannons present.
	 */
	void calculateScore();

	/*
	 * Pass in this block to the current player's pointer and set its position.
	 */
	void giveBlock();
};

