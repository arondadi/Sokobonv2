#ifndef BLOCK_H
#define BLOCK_H

#include <SDL.h>

#include "Globals.h"

enum colors { BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE };

enum states { FREE, COMBINED };

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

	void draw(SDL_Renderer *renderer, enum colors color);

	// Change current state
	void ChangeState(states state);

	// Get current state
	states GetState();

private:
	int m_x, m_y;

	states m_state;
};

#endif // !BLOCK_h

