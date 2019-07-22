#ifndef LEVELPTR_H
#define LEVELPTR_H

#include <SDL.h>
#include <vector>
#include <time.h> 

#include "Globals.h"
#include "Block.h"
#include "Player.h"


class LevelPtr
{
public:
	LevelPtr();
	~LevelPtr();

	void draw(SDL_Renderer *renderer);

	// Call for updated game state
	void update(int player_x, int player_y);

	bool game_over_check(int player_x, int player_y);

	bool check_possible_move(int current_x, int current_y, int dx, int dy);

	bool checkBlockMove(int currentX, int currentY, int dx, int dy, int checkIndex);

	// Check if entity at (x,y) collides with the board
	bool check_collision(int x, int y);

	// Reset board array at restart
	void reset_board();

	//TODO(Aron): Add function to combine blocks into Tetrominos
	// Player presses a button to change the state of blocks he is facing
	// Adjacent blocks also change state
	// Depending on the state of the block, it can be moved or not (like Tetris)
	// Block moving to be implemented in game with controls

	bool CheckTargetPos(int player_x, int player_y, facing Facing);

	// Move all blocks that have been combined
	void MoveCombinedBlocks(int dx, int dy);

private:
	//std::vector<Block> m_blocks;
	std::vector<Block> m_boundary;

	// Insert walls on the board
	void intilize_board();

	//TODO(Aron): Implement a m_board array of pointers, pointing to generated blocks in memory. 
	//Get rid of m_blocks and use m_board pointers instead

	// Data structure to keep track of the location of blocks in the board
	Block *m_board[globals::SCREEN_WIDTH_BLOCK][globals::SCREEN_HEIGHT_BLOCK];
};

#endif // !LEVELPTR_H
