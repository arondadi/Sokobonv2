#ifndef GAME_H
#define GAME_H


#include <SDL.h>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <time.h>  

#include "Globals.h"
#include "Player.h"
#include "Level.h"
#include "Input.h"
#include "Block.h"

class Game
{
public:
	Game();
	~Game();
	void gameLoop();

private:
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Surface *m_screenSurface;

	Player m_player;
	std::vector<Block> m_blocks;
	Level m_level;

	// Checks for loose conditions
	bool game_over;

	// Natural fall of blocks over time
	int time_block_falling;

	// Data structure to keep track of the location of blocks in the board
	bool m_board[globals::SCREEN_WIDTH / globals::BLOCK_SIZE][globals::SCREEN_HEIGHT / globals::BLOCK_SIZE];

	void draw(SDL_Renderer *m_renderer);

	void update();

	void restart();




};


#endif // !GAME_H
