#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>

#include "Globals.h"

class Player
{
public:

	Player();
	// Player constructor takes in the starting location of the player
	Player(int x, int y);
	~Player();

	// Draw the player on the backbuffer
	void draw(SDL_Renderer *renderer);

	// Move player dx in x direction and dy in y direction
	void move(int dx, int dy);

	// Move player to spawn point location
	void move_to_spawn();

	// Get current X position
	int getCurrentX();
	// Get current Y position
	int getCurrentY();
	// Get prev X position
	int getPrevX();
	// Get prev Y position
	int getPrevY();

private:
	int m_currentX, m_currentY;
	int m_prevX, m_prevY;

};

#endif // !PLAYER_H
