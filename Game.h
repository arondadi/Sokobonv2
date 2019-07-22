#ifndef GAME_H
#define GAME_H


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <time.h>  

#include "Globals.h"
#include "Player.h"
#include "Level.h"
#include "LevelPtr.h"
#include "Input.h"
#include "Block.h"
#include "UI.h"

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

	LevelPtr test_level;

	UI m_ui;

	// Checks for loose conditions
	bool game_over;

	// Natural fall of blocks over time
	int time_block_falling;

	// Data structure to keep track of the location of blocks in the board
	bool m_board[globals::SCREEN_WIDTH / globals::BLOCK_SIZE][globals::SCREEN_HEIGHT / globals::BLOCK_SIZE];

	void draw(SDL_Renderer *m_renderer, float frame_rate);

	void update();

	void restart();

	// Initialize SDL
	bool init();

	// Moving blocks or player
	bool move_blocks;

	// Check if there is block in front of player
	bool BlockByPlayer;
};


#endif // !GAME_H
