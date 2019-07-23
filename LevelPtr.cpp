#include "LevelPtr.h"

LevelPtr::LevelPtr()
{

	//for (int indexW = 0; indexW < globals::BOARD_WIDTH; indexW++)
	//{
	//	for (int indexH = 0; indexH < globals::BOARD_HEIGHT; indexH++)
	//	{
	//		m_board[indexW][indexH] = new Block();
	//	}
	//}

	// Initialize random seed so rand is not the same every time
	srand(time(NULL));

	// Draw the walls
	this->intilize_board();

	for (int indexW = 0; indexW < globals::BOARD_WIDTH; indexW++)
	{
		for (int indexH = 0; indexH < globals::BOARD_HEIGHT; indexH++)
		{
			this->m_board[indexW][indexH] = new Block(indexH * globals::BLOCK_SIZE, indexW * globals::BLOCK_SIZE, EMPTY);
		}
	}
}


LevelPtr::~LevelPtr()
{

}

void LevelPtr::intilize_board()
{
	for (int index_height = 0; index_height < globals::SCREEN_HEIGHT; index_height++)
	{
		m_boundary.push_back(Block((globals::SCREEN_WIDTH_BLOCK + globals::BOARD_WIDTH) / 2 * globals::BLOCK_SIZE, index_height * globals::BLOCK_SIZE, EMPTY));
		m_boundary.push_back(Block((globals::SCREEN_WIDTH_BLOCK - globals::BOARD_WIDTH - 1) / 2 * globals::BLOCK_SIZE, index_height * globals::BLOCK_SIZE, EMPTY));
	}


}


void LevelPtr::draw(SDL_Renderer *renderer)
{
	for (int indexW = 0; indexW < globals::BOARD_WIDTH; indexW++)
	{
		for (int indexH = 0; indexH < globals::BOARD_HEIGHT; indexH++)
		{
			if (m_board[indexW][indexH]->GetState() == FREE)
			{
				m_board[indexW][indexH]->draw(renderer, RED);
			}
			else if (m_board[indexW][indexH]->GetState() == COMBINED)
			{
				m_board[indexW][indexH]->draw(renderer, GREEN);
			}
		}
	}

	for (int i = 0; i < m_boundary.size(); i++)
	{
		m_boundary.at(i).draw(renderer, BLUE);
	}
}

//
//bool LevelPtr::check_possible_move(int current_x, int current_y, int dx, int dy)
//{
//	for (int i = 0; i < m_boundary.size(); i++)
//	{
//		if (m_boundary.at(i).getX() == current_x && m_boundary.at(i).getY() == current_y)
//		{
//			return false;
//		}
//	}
//
//	for (int i = 0; i < m_blocks.size(); i++)
//	{
//		if (m_blocks.at(i).getX() == current_x && m_blocks.at(i).getY() == current_y)
//		{
//			// Check if the blocks are being pushed out of bound
//			// dx != 0 so player can push blocks along edge
//			if (dx != 0)
//			{
//				if (m_blocks.at(i).getX() + globals::BLOCK_SIZE == (globals::SCREEN_WIDTH_BLOCK + globals::BOARD_WIDTH) / 2 * globals::BLOCK_SIZE
//					|| m_blocks.at(i).getX() - globals::BLOCK_SIZE == (globals::SCREEN_WIDTH_BLOCK - globals::BOARD_WIDTH - 1) / 2 * globals::BLOCK_SIZE)
//				{
//					return false;
//				}
//			}
//			else if (m_blocks.at(i).getY() == 0)
//			{
//				// Cannot push blocks above board field
//				return false;
//			}
//
//
//			if (m_board[(m_blocks.at(i).getX()) / globals::BLOCK_SIZE + dx][(m_blocks.at(i).getY()) / globals::BLOCK_SIZE + dy] == false)
//			{
//				// Changes the place of the moved block to it new place in the board
//				m_board[(m_blocks.at(i).getX()) / globals::BLOCK_SIZE + dx][(m_blocks.at(i).getY()) / globals::BLOCK_SIZE + dy] = true;
//				// Remove the blocks previous place in the board
//				m_board[(m_blocks.at(i).getX()) / globals::BLOCK_SIZE][(m_blocks.at(i).getY()) / globals::BLOCK_SIZE] = false;
//
//				// Moves the blocks location in the game
//				m_blocks.at(i).move(dx, dy);
//
//				return true;
//			}
//			else
//			{
//				// If the player cannot move a block because another block is behind it the player is moved back before rendering
//				return false;
//			}
//		}
//	}
//}
//
//bool LevelPtr::check_collision(int x, int y)
//{
//	for (int i = 0; i < m_blocks.size(); i++)
//	{
//		if (m_blocks.at(i).getX() == x && m_blocks.at(i).getY() == y)
//		{
//			return true;
//		}
//	}
//
//	return false;
//}
//
//bool LevelPtr::game_over_check(int player_x, int player_y)
//{
//	// Game over check
//	for (int i = 0; i < m_blocks.size(); i++)
//	{
//		// Check if block is one position above player
//		if (m_blocks.at(i).getX() == player_x && m_blocks.at(i).getY() + globals::BLOCK_SIZE == player_y)
//		{
//			if (m_board[player_x / globals::BLOCK_SIZE][(player_y / globals::BLOCK_SIZE) - 1] == true && m_board[player_x / globals::BLOCK_SIZE][(player_y / globals::BLOCK_SIZE) - 2] == true)
//			{
//				printf("GAME OVER! \n");
//				return true;
//				break;
//			}
//
//		}
//	}
//
//	return false;
//}
//
//void LevelPtr::reset_board()
//{
//	m_blocks.clear();
//
//	// Reset m_board 
//	for (int i = 0; i < globals::SCREEN_WIDTH_BLOCK; i++)
//	{
//		for (int j = 0; j < globals::SCREEN_HEIGHT_BLOCK; j++)
//		{
//			m_board[i][j] = false;
//		}
//
//	}
//}
//
//bool LevelPtr::CheckTargetPos(int player_x, int player_y, facing Facing)
//{
//	//TODO(Aron): Access m_blocks in memory (pointer?) to see the (x,y) cordinates and change state
//	for (int i = 0; i < m_blocks.size(); i++)
//	{
//		switch (Facing)
//		{
//		case RIGHT:
//			if (m_blocks.at(i).getX() == player_x + globals::BLOCK_SIZE && m_blocks.at(i).getY() == player_y)
//			{
//				m_blocks.at(i).ChangeState(COMBINED);
//				return true;
//			}
//		case LEFT:
//			if (m_blocks.at(i).getX() == player_x - globals::BLOCK_SIZE && m_blocks.at(i).getY() == player_y)
//			{
//				m_blocks.at(i).ChangeState(COMBINED);
//				return true;
//			}
//		case UP:
//			if (m_blocks.at(i).getX() == player_x && m_blocks.at(i).getY() == player_y - globals::BLOCK_SIZE)
//			{
//				m_blocks.at(i).ChangeState(COMBINED);
//				return true;
//			}
//		case DOWN:
//			if (m_blocks.at(i).getX() == player_x && m_blocks.at(i).getY() == player_y + globals::BLOCK_SIZE)
//			{
//				m_blocks.at(i).ChangeState(COMBINED);
//				return true;
//			}
//		}
//	}
//
//	return false;
//}
//
void LevelPtr::update(int player_x, int player_y)
{
	//TODO(Aron): Make it so that if a block is being pushed by player it does not fall down

	// Moves every block on the board and for the renderer
	for (int indexW = 0; indexW < globals::BOARD_WIDTH; indexW++)
	{
		for (int indexH = 0; indexH < globals::BOARD_HEIGHT; indexH++)
		{
			if (indexH > 0)
			{
				// Check if block is one position above player
				if (!(m_board[indexW][indexH]->getX() == player_x && m_board[indexW][indexH - 1]->getY() == player_y))
				{
					// Moves the block in the renderer
					m_board[indexW][indexH]->move(0, 1);

					printf("indexW: %d, indexH: %d \n", indexW, indexH);
					
					if (indexH < globals::BOARD_HEIGHT - 1)
					{
						// Moves the block on the board
						*&m_board[indexW][indexH] = m_board[indexW][indexH + 1];
						m_board[indexW][indexH]->ChangeState(EMPTY);
					}
					else
					{
						m_board[indexW][indexH]->ChangeState(EMPTY);
					}

				}
			}
		}
	}

	// Create a spawn position at the top block level 10 block_sizes wide in the middle
	int spawn_pos_pixels = (((rand() % 10)) * globals::BLOCK_SIZE) + (globals::SCREEN_WIDTH / 2 - globals::BLOCK_SIZE * 5);
	int spawn_pos = ((rand() % 10)) + (globals::BOARD_WIDTH / 2 -  5);

	//TODO(Aron): make a new Block( allocate memory for it ) and point m_board to it

	Block newBlock = Block(spawn_pos_pixels, 0, FREE);

	m_board[spawn_pos][0]->SpawnBlock(spawn_pos_pixels, 0);
	
}
//
////TODO(Aron): Implement boundaries for moving blocks
//// Move blocks position on m_board
//void LevelPtr::MoveCombinedBlocks(int dx, int dy)
//{
//	for (int indexBlock = 0; indexBlock < m_blocks.size(); indexBlock++)
//	{
//		if (m_blocks.at(indexBlock).GetState() == COMBINED)
//		{
//			(this->checkBlockMove(m_blocks.at(indexBlock).getX(), m_blocks.at(indexBlock).getY(), dx, dy, indexBlock));
//
//			//// Move the COMBINED block by (dx, dy) in possible
//			//if ((this->checkBlockMove(m_blocks.at(indexBlock).getX(), m_blocks.at(indexBlock).getY(), dx, dy, indexBlock)))
//			//{
//			//	//m_blocks.at(indexBlock).move(dx, dy);
//			//}
//		}
//	}
//}
//
//bool LevelPtr::checkBlockMove(int currentX, int currentY, int dx, int dy, int checkIndex)
//{
//	for (int indexBound = 0; indexBound < m_boundary.size(); indexBound++)
//	{
//		if (m_boundary.at(indexBound).getX() == (currentX + dx * globals::BLOCK_SIZE) && m_boundary.at(indexBound).getY() == (currentY /*+ dy*globals::BLOCK_SIZE*/))
//		{
//			return false;
//		}
//	}
//
//	for (int indexBlock = 0; indexBlock < m_blocks.size(); indexBlock++)
//	{
//		if (m_blocks.at(indexBlock).getX() == currentX && m_blocks.at(indexBlock).getY() == currentY) // && checkIndex != indexBlock
//		{
//			if (m_board[(m_blocks.at(indexBlock).getX()) / globals::BLOCK_SIZE + dx][(m_blocks.at(indexBlock).getY()) / globals::BLOCK_SIZE + dy] == false) // && checkIndex != indexBlock
//			{
//				// Changes the place of the moved block to it new place in the board
//				m_board[(m_blocks.at(indexBlock).getX()) / globals::BLOCK_SIZE + dx][(m_blocks.at(indexBlock).getY()) / globals::BLOCK_SIZE + dy] = true;
//				// Remove the blocks previous place in the board
//				m_board[(m_blocks.at(indexBlock).getX()) / globals::BLOCK_SIZE][(m_blocks.at(indexBlock).getY()) / globals::BLOCK_SIZE] = false;
//
//				// Moves the blocks location in the game
//				m_blocks.at(indexBlock).move(dx, dy);
//
//				return true;
//			}
//			else
//			{
//				// If the player cannot move a block because another block is behind it the player is moved back before rendering
//				return false;
//			}
//		}
//	}
//
//	return true;
//}