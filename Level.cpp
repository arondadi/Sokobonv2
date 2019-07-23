#include "Level.h"

Level::Level():
	m_board{false}
{

	// Initialize random seed so rand is not the same every time
	srand(time(NULL));

	// Draw the walls
	this->intilize_board();

	//for (int index_width = 0; index_width < globals::SCREEN_WIDTH_BLOCK; index_width++)
	//{
	//	for (int index_height = 0; index_height < globals::SCREEN_HEIGHT_BLOCK; index_height++)
	//	{
	//		m_board[index_width][index_height] = Block(0, 0);
	//	}
	//}
}


Level::~Level()
{

}

void Level::intilize_board()
{
	for(int index_height = 0; index_height < globals::SCREEN_HEIGHT; index_height++)
	{
		m_boundary.push_back(Block((globals::SCREEN_WIDTH_BLOCK + globals::BOARD_WIDTH) / 2 * globals::BLOCK_SIZE, index_height * globals::BLOCK_SIZE, EMPTY));
		m_boundary.push_back(Block((globals::SCREEN_WIDTH_BLOCK - globals::BOARD_WIDTH - 1) / 2 * globals::BLOCK_SIZE, index_height * globals::BLOCK_SIZE, EMPTY));
	}
}


void Level::draw(SDL_Renderer *renderer)
{
	for (int i = 0; i < m_blocks.size(); i++)
	{
		if (m_blocks.at(i).GetState() == FREE)
		{
			m_blocks.at(i).draw(renderer, RED);
		}
		else if (m_blocks.at(i).GetState() == COMBINED)
		{
			m_blocks.at(i).draw(renderer, GREEN);
		}
		
	}

	for (int i = 0; i < m_boundary.size(); i++)
	{
		m_boundary.at(i).draw(renderer, BLUE);
	}
}

bool Level::check_possible_move(int current_x, int current_y, int dx, int dy)
{
	for (int i = 0; i < m_boundary.size(); i++)
	{
		if (m_boundary.at(i).getX() == current_x && m_boundary.at(i).getY() == current_y)
		{
			return false;
		}
	}

	for (int i = 0; i < m_blocks.size(); i++)
	{
		if (m_blocks.at(i).getX() == current_x && m_blocks.at(i).getY() == current_y)
		{
			// Check if the blocks are being pushed out of bound
			// dx != 0 so player can push blocks along edge
			if (dx != 0) 
			{
				if (m_blocks.at(i).getX() + globals::BLOCK_SIZE == (globals::SCREEN_WIDTH_BLOCK + globals::BOARD_WIDTH) / 2 * globals::BLOCK_SIZE
					|| m_blocks.at(i).getX() - globals::BLOCK_SIZE == (globals::SCREEN_WIDTH_BLOCK - globals::BOARD_WIDTH - 1) / 2 * globals::BLOCK_SIZE)
				{
					return false;
				}
			}
			else if (m_blocks.at(i).getY() == 0)
			{
				// Cannot push blocks above board field
				return false;
			}
			

			if (m_board[(m_blocks.at(i).getX()) / globals::BLOCK_SIZE + dx][(m_blocks.at(i).getY()) / globals::BLOCK_SIZE + dy] == false)
			{
				// Changes the place of the moved block to it new place in the board
				m_board[(m_blocks.at(i).getX()) / globals::BLOCK_SIZE + dx][(m_blocks.at(i).getY()) / globals::BLOCK_SIZE + dy] = true;
				// Remove the blocks previous place in the board
				m_board[(m_blocks.at(i).getX()) / globals::BLOCK_SIZE][(m_blocks.at(i).getY()) / globals::BLOCK_SIZE] = false;

				// Moves the blocks location in the game
				m_blocks.at(i).move(dx, dy);

				return true;
			}
			else
			{
				// If the player cannot move a block because another block is behind it the player is moved back before rendering
				return false;
			}
		}
	}
}

bool Level::check_collision(int x, int y)
{
	for (int i = 0; i < m_blocks.size(); i++)
	{
		if (m_blocks.at(i).getX() == x && m_blocks.at(i).getY() == y)
		{
			return true;
		}
	}

	return false;
}

bool Level::game_over_check(int player_x, int player_y)
{
	// Game over check
	for (int i = 0; i < m_blocks.size(); i++)
	{
		// Check if block is one position above player
		if (m_blocks.at(i).getX() == player_x && m_blocks.at(i).getY() + globals::BLOCK_SIZE == player_y)
		{
			if (m_board[player_x / globals::BLOCK_SIZE][(player_y / globals::BLOCK_SIZE) - 1] == true && m_board[player_x / globals::BLOCK_SIZE][(player_y / globals::BLOCK_SIZE) - 2] == true)
			{
				printf("GAME OVER! \n");
				return true;
				break;
			}

		}
	}

	return false;
}

void Level::reset_board()
{
	m_blocks.clear();

	// Reset m_board 
	for (int i = 0; i < globals::SCREEN_WIDTH_BLOCK; i++)
	{
		for (int j = 0; j < globals::SCREEN_HEIGHT_BLOCK; j++)
		{
			m_board[i][j] = false;
		}

	}
}

bool Level::CheckTargetPos(int player_x, int player_y, facing Facing)
{
	//TODO(Aron): Access m_blocks in memory (pointer?) to see the (x,y) cordinates and change state
	for (int i = 0; i < m_blocks.size(); i++)
	{
		switch (Facing)
		{
		case RIGHT:
			if (m_blocks.at(i).getX() == player_x + globals::BLOCK_SIZE && m_blocks.at(i).getY() == player_y)
			{
				m_blocks.at(i).ChangeState(COMBINED);
				return true;
			}
		case LEFT:
			if (m_blocks.at(i).getX() == player_x - globals::BLOCK_SIZE && m_blocks.at(i).getY() == player_y)
			{
				m_blocks.at(i).ChangeState(COMBINED);
				return true;
			}
		case UP:
			if (m_blocks.at(i).getX() == player_x && m_blocks.at(i).getY() == player_y - globals::BLOCK_SIZE)
			{
				m_blocks.at(i).ChangeState(COMBINED);
				return true;
			}
		case DOWN:
			if (m_blocks.at(i).getX() == player_x && m_blocks.at(i).getY() == player_y + globals::BLOCK_SIZE)
			{
				m_blocks.at(i).ChangeState(COMBINED);
				return true;
			}
		}
	}

	return false;
}

void Level::update(int player_x, int player_y)
{
	//TODO(Aron): Make it so that if a block is being pushed by player it does not fall down

	// Moves every block on the board and for the renderer
	for (int i = 0; i < m_blocks.size(); i++)
	{
		// Check if block is one position above player
		if (!(m_blocks.at(i).getX() == player_x && m_blocks.at(i).getY() + globals::BLOCK_SIZE == player_y))
		{
			// Moves every block on the board if there is a block
			m_board[(m_blocks.at(i).getX()) / globals::BLOCK_SIZE][(m_blocks.at(i).getY()) / globals::BLOCK_SIZE] = false;
			m_board[(m_blocks.at(i).getX()) / globals::BLOCK_SIZE][((m_blocks.at(i).getY()) + globals::BLOCK_SIZE) / globals::BLOCK_SIZE] = true;

			// Move the rendered block on screen
			m_blocks.at(i).move(0, 1);
		}

	}

	// Create a spawn position at the top block level 10 block_sizes wide in the middle
	int spawn_pos = (((rand() % 10)) * globals::BLOCK_SIZE) + (globals::SCREEN_WIDTH / 2 - globals::BLOCK_SIZE * 5);

	// Makes a new block in the m_block vector
	m_blocks.push_back(Block(spawn_pos, - globals::BLOCK_SIZE, FREE));

	// Creates the block on the board
	m_board[spawn_pos / globals::BLOCK_SIZE][0] = true;
}

// Move blocks position on m_board
void Level::MoveCombinedBlocks(int dx, int dy)
{
	for (int indexBlock = 0; indexBlock < m_blocks.size(); indexBlock++)
	{
		if (m_blocks.at(indexBlock).GetState() == COMBINED)
		{
			(this->checkBlockMove(m_blocks.at(indexBlock).getX(), m_blocks.at(indexBlock).getY(), dx, dy, indexBlock));

			//// Move the COMBINED block by (dx, dy) in possible
			//if ((this->checkBlockMove(m_blocks.at(indexBlock).getX(), m_blocks.at(indexBlock).getY(), dx, dy, indexBlock)))
			//{
			//	//m_blocks.at(indexBlock).move(dx, dy);
			//}
		}
	}
}

bool Level::checkBlockMove(int currentX, int currentY, int dx, int dy, int checkIndex)
{
	for (int indexBound = 0; indexBound < m_boundary.size(); indexBound++)
	{
		if (m_boundary.at(indexBound).getX() == (currentX + dx*globals::BLOCK_SIZE) && m_boundary.at(indexBound).getY() == (currentY /*+ dy*globals::BLOCK_SIZE*/))
		{
			return false;
		}
	}

	for (int indexBlock = 0; indexBlock < m_blocks.size(); indexBlock++)
	{
		if (m_blocks.at(indexBlock).getX() == currentX && m_blocks.at(indexBlock).getY() == currentY) // && checkIndex != indexBlock
		{
			if (m_board[(m_blocks.at(indexBlock).getX()) / globals::BLOCK_SIZE + dx][(m_blocks.at(indexBlock).getY()) / globals::BLOCK_SIZE + dy] == false) // && checkIndex != indexBlock
			{
				// Changes the place of the moved block to it new place in the board
				m_board[(m_blocks.at(indexBlock).getX()) / globals::BLOCK_SIZE + dx][(m_blocks.at(indexBlock).getY()) / globals::BLOCK_SIZE + dy] = true;
				// Remove the blocks previous place in the board
				m_board[(m_blocks.at(indexBlock).getX()) / globals::BLOCK_SIZE][(m_blocks.at(indexBlock).getY()) / globals::BLOCK_SIZE] = false;

				// Moves the blocks location in the game
				m_blocks.at(indexBlock).move(dx, dy);

				return true;
			}
			else
			{
				// If the player cannot move a block because another block is behind it the player is moved back before rendering
				return false;
			}
		}
	}

	return true;
}