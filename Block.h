#ifndef BLOCK_H
#define BLOCK_H

#include <SDL.h>

#include "Globals.h"

class Block
{
public:
	// Default constructor
	Block();

	// Constructor
	Block(int x, int y);

	// Deconstructor
	~Block();

	// Move according to collision with player
	void move(int dx, int dy);

	// Get X position
	int getX();

	// Get Y position
	int getY();

	void draw(SDL_Renderer *renderer);

private:
	int m_x, m_y;
};

#endif // !BLOCK_h

