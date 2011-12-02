#pragma once
#include "Block.h"
#include "Explosion.h"

// player keys for processing input
const int NUM_KEYS = 6;
const int PLAYER_KEY_UP = 0;
const int PLAYER_KEY_DOWN = 1;
const int PLAYER_KEY_LEFT = 2;
const int PLAYER_KEY_RIGHT = 3;
const int PLAYER_KEY_ACT = 4;
const int PLAYER_KEY_ROTATE = 5;

class Player : public Geode
{
  public:
    // player region bounds
    float minX, 
		  minZ, 
		  maxX, 
		  maxZ; 
    // the current block for the player to place
    Geode* currentBlock;
    // the starting position - also the position for the fortress to be put up
    Vector3 origin;
	// this player's input control keys
	char keys[6];
	// a pointer to the 2 dimensional array of the player's blocks,
	// which are themselves abstract to any kind of "block"
	Geode*** region;
	// helper values
	int rows, columns, spaces;
	// player's emblem texture which gets placed on all of the player's tiles in enclosed portions
	GLuint emblem;

	/* 
	 * Initialize this player. 
	 * The origin is the destination of the fortress as well as the cursor starting position.
	 * The key commands are an abstraction of how this player's input is represented.
	 * The bounds are the restrictions on which section of the map this player can place blocks on.
	 * The emblem is the texture put in on enclosed portions of the player's region.
	 */
    Player(Vector3 o, float xmin, float xmax, float zmin, float zmax, char keycommands[], GLuint e) : 
	origin(o), minX(xmin), maxX(xmax), minZ(zmin), maxZ(zmax), emblem(e)
	{
		// set in key commands
		for(int i = 0; i < NUM_KEYS; ++i)
			keys[i] = keycommands[i];

		// create the dimensions of the region
		rows = (maxX - minX) / BLOCK_SIZE;
		columns = (maxZ - minZ) / BLOCK_SIZE;
		spaces = rows * columns;

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
	 * Checks collisions and tries to place the current cannon.
	 * If the texture below is not an emblem, then we can't place.
	 */
	void placeCannon();

	/*
	 * Draw all of the player's objects that are currently on screen.
	 * Draw the current block. 
	 * //LATER// Draw the score, player name, and upcoming block view. 
	 */
    void render();

	/*
	 * Handle the player's input.
	 */
	void handleInputs(char key);

	/*
	 * Calculate this player's score based on the number of emblem textures and cannons present.
	 */
	void calculateScore();
};

