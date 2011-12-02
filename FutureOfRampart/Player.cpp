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
	// no overriding locations
	if(region[currR][currC] == NULL)
	{
		currentBlock->place();
		region[currR][currC] = currentBlock;
		currentBlock = NULL;
	}
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
		}
	}
	// probably nothing for the purposes of this demonstration
	else if(key == keys[PLAYER_KEY_GIVE])
	{
		giveBlock();
	}

	cout << "CURRENT LOCATION: " << "ROW: " << currR << ", COL: " << currC << endl;
}

void Player::calculateScore()
{

}

void Player::giveBlock()
{
	Block* newB = new Block(Vector3(1.0f, 1.0f, 1.0f), BLOCK_FRONT, 
		BLOCK_LEFT, BLOCK_LEFT, BLOCK_LEFT, 
		BLOCK_LEFT, BLOCK_LEFT, true);
	
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

/*
struct bfsnode {
  int i, j;
  bfsnode * previous;
  bfsnode(int I, int J, bfsnode * prev) : i(I), j(J), previous(prev) {}
  bool operator==(const bfsnode& n) { return i == n.i && j == n.j; }
  bool operator!=(const bfsnode& n) { return i != n.i || j != n.j; }
};
 
struct enclosure {
  vector< pair<int, int> > squares;
  enclosure() {}
  enclosure(const vector<bfsnode>& cycle) {
  }
  static bool valid(const vector<bfsnode>& cycle) {
    // NB. this may not always work!
    int imin = rows, imax = 0, jmin = columns, jmax = 0;
    for(vector<bfsnode>::iterator p = cycle.begin(); p != cycle.end(); ++p) {
      if(p->i > imax) imax = p->i;
      if(p->i < imin) imin = p->i;
      if(p->j > jmax) jmax = p->j;
      if(p->j < jmin) jmin = p->j;
    }
    return (imax - imin > 1) && (jmax - jmin > 1);
  }
};
 
bool in(const vector<bfsnode>& v, const bfsnode& i) {
  for(vector<bfsnode>::iterator p = v.begin(); p != v.end(); ++p)
    if(*p == i)
      return true;
  return false;
}
 
vector<bfsnode> cycleFrom(const bfsnode& n) {
  vector<bfsnode> v;
  bfsnode ptr = n;
  for(; ptr.previous; ptr = ptr.previous) v.push_back(ptr);
  return v;
}
 
void find_enclosed_spaces() {
  queue<bfsnode> q;
  vector<bfsnode> t;
 
  for(int i = 0; i < rows; ++i)
    for(int j = 0; j < columns; ++j)
      if(region[i][j]) {
        q.push_back(bfsnode(i, j, NULL));
        break;
      }
 
  while(q.size() > 0) {
    int i, j;
    bfsnode n = q.pop_front();
    t.push_back(n);
    i = n.i - 1;
    j = n.j - 1;
    if(i >= 0 && j >= 0 && region[i][j]) {
      bfsnode next(i, j, n);
      if(next != n) {
        if(in(t, next)) {
          vector<bfsnode> c = cycleFrom(n);
          if(enclosure::valid(c))
            result.push_back(enclosure(c));
          else
            q.push_back(next);
        }
        else
          q.push_back(next);
      }
    }
    i = n.i - 1;
    j = n.j + 1;
    if(i >= 0 && j < columns && region[i][j]) {
      bfsnode next(i, j, n);
      if(next != n) {
        if(in(t, next)) {
          vector<bfsnode> c = cycleFrom(n);
          if(enclosure::valid(c))
            result.push_back(enclosure(c));
          else
            q.push_back(next);
        }
        else
          q.push_back(next);
      }
    }
    i = n.i + 1;
    j = n.j - 1;
    if(i < rows && j >= 0 && region[i][j]) {
      bfsnode next(i, j, n);
      if(next != n) {
        if(in(t, next)) {
          vector<bfsnode> c = cycleFrom(n);
          if(enclosure::valid(c))
            result.push_back(enclosure(c));
          else
            q.push_back(next);
        }
        else
          q.push_back(next);
      }
    }
    i = n.i + 1;
    j = n.j + 1;
    if(i < rows && j < columns && region[i][j]) {
      bfsnode next(i, j, n);
      if(next != n) {
        if(in(t, next)) {
          vector<bfsnode> c = cycleFrom(n);
          if(enclosure::valid(c))
            result.push_back(enclosure(c));
          else
            q.push_back(next);
        }
        else
          q.push_back(next);
      }
    }
  }
}
*/
