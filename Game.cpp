#include "Game.h"

#include <algorithm>



Game::Game():
	m_window(NULL),
	m_screenSurface(NULL),
	m_board{false},
	time_block_falling(SDL_GetTicks()),
	game_over(false)
{

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, SDL_WINDOW_OPENGL, &m_window, &m_renderer);
		if (m_window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			// Gameloop that runs indefenently
			gameLoop();
			
		}
	}
}

Game::~Game()
{
	// Destroy renderer
	SDL_DestroyRenderer(m_renderer);

	// Destroy window
	SDL_DestroyWindow(m_window);

	//Quit SDL subsystems
	SDL_Quit();
}

void Game::gameLoop()
{
	Input input;

	// Spawns the player at position (x,y)
	m_player = Player(globals::PLAYER_SPAWN_X, globals::PLAYER_SPAWN_Y);

	SDL_Event event;

	// Initialize random seed so rand is not the same every time
	srand(time(NULL));

	//// Adding blocks manually
	//m_blocks.push_back(Block(globals::SCREEN_WIDTH / 2, 128+32));
	//m_blocks.push_back(Block(globals::SCREEN_WIDTH / 2, 128+64));
	//m_blocks.push_back(Block(globals::SCREEN_WIDTH / 2 + 32, 128));
	//m_blocks.push_back(Block(globals::SCREEN_WIDTH / 2 + 64, 128));

	//for (int pos = 0; pos < m_blocks.size(); pos++)
	//{
	//	m_board[m_blocks.at(pos).getX() / globals::BLOCK_SIZE][m_blocks.at(pos).getY() / globals::BLOCK_SIZE ] = true;
	//}


	//m_level = Level();

	int time_since_last_frame = SDL_GetTicks();

	int time_last_move = SDL_GetTicks();

	while (true)
	{
		// Endless loop while the window is not x-d out or escape
		while (!game_over)
		{
			// Movement tick
			int time_elapsed_move = SDL_GetTicks();

			if (time_elapsed_move - time_last_move > globals::MOVEMENT_TICK)
			{
				input.beginNewFrame();

				if (SDL_PollEvent(&event)) {
					if (event.type == SDL_KEYDOWN) {
						if (event.key.repeat == 0) {
							input.keyDownEvent(event);
						}
					}
					else if (event.type == SDL_KEYUP) {
						input.keyUpEvent(event);
					}
					else if (event.type == SDL_QUIT) {
						return;
					}
				}

				if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
					return;
				}
				else if (input.wasKeyPressed(SDL_SCANCODE_LEFT) == true || input.isKeyHeld(SDL_SCANCODE_LEFT)) {
					this->m_player.move(-1, 0);
				}
				else if (input.wasKeyPressed(SDL_SCANCODE_RIGHT) == true || input.isKeyHeld(SDL_SCANCODE_RIGHT)) {
					this->m_player.move(1, 0);
				}
				else if (input.wasKeyPressed(SDL_SCANCODE_DOWN) == true || input.isKeyHeld(SDL_SCANCODE_DOWN)) {
					this->m_player.move(0, 1);
				}
				else if (input.wasKeyPressed(SDL_SCANCODE_UP) == true || input.isKeyHeld(SDL_SCANCODE_UP)) {
					this->m_player.move(0, -1);
				}

				time_last_move = SDL_GetTicks();
			}


			int time_elapsed = SDL_GetTicks();

			if (time_elapsed - time_since_last_frame > 1000 / globals::FRAME_RATE)
			{
				// printf("%d \n", 1000 / (time_elapsed - time_since_last_frame) );
				this->update();

				this->draw(m_renderer);

				time_since_last_frame = SDL_GetTicks();
			}

		}

		// Freezes the current renderer
		// The player can X out of window
		while (game_over)
		{
			input.beginNewFrame();

			if (SDL_PollEvent(&event)) {
				if (event.type == SDL_KEYDOWN) {
					if (event.key.repeat == 0) {
						input.keyDownEvent(event);
					}
				}
				else if (event.type == SDL_KEYUP) {
					input.keyUpEvent(event);
				}
				else if (event.type == SDL_QUIT) {
					return;
				}
			}

			if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
				return;
			}
			if (input.wasKeyPressed(SDL_SCANCODE_SPACE) == true) {
				printf("New game!");
				game_over = false;
			}


			this->draw(m_renderer);

		}

		// Keep timers updated
		time_since_last_frame = SDL_GetTicks();
		time_last_move = SDL_GetTicks();
		time_block_falling = SDL_GetTicks();

		// TODO: Implement restart function for game
		this->restart();
	}
}

void Game::update()
{
	for (int i = 0; i < m_blocks.size(); i++)
	{
		if (m_blocks.at(i).getX() == m_player.getCurrentX() && m_blocks.at(i).getY() == m_player.getCurrentY())
		{
			// The players change in position (in block size chuncks) 
			int dx = (m_player.getCurrentX() - m_player.getPrevX()) / globals::BLOCK_SIZE;
			int dy = (m_player.getCurrentY() - m_player.getPrevY()) / globals::BLOCK_SIZE;

			if (m_board[(m_blocks.at(i).getX()) / globals::BLOCK_SIZE + dx][(m_blocks.at(i).getY()) / globals::BLOCK_SIZE + dy] == false)
			{
				// Changes the place of the moved block to it new place in the board
				m_board[(m_blocks.at(i).getX()) / globals::BLOCK_SIZE + dy][(m_blocks.at(i).getY()) / globals::BLOCK_SIZE + dy] = true;
				// Remove the blocks previous place in the board
				m_board[(m_blocks.at(i).getX()) / globals::BLOCK_SIZE][(m_blocks.at(i).getY()) / globals::BLOCK_SIZE] = false;

				// Moves the blocks location in the game
				m_blocks.at(i).move(dx, dy);

			}
			else
			{
				// If the player cannot move a block because another block is behind it the player is moved back before rendering
				m_player.move(-dx, -dy);
			}
		}
	}

	// Moves block every block down every second and spawns a new block
	if (SDL_GetTicks() > time_block_falling)
	{
		time_block_falling += 1000;


		// TODO: does not work when block is being push up
		// Game over check
		for (int i = 0; i < m_blocks.size(); i++)
		{
			// Check if block is one position above player
			if (m_blocks.at(i).getX() == m_player.getCurrentX() && m_blocks.at(i).getY() + 32 == m_player.getCurrentY())
			{
				if (m_board[m_player.getCurrentX() / globals::BLOCK_SIZE][(m_player.getCurrentY() / globals::BLOCK_SIZE) - 1] == true && m_board[m_player.getCurrentX() / globals::BLOCK_SIZE][(m_player.getCurrentY() / globals::BLOCK_SIZE) - 2] == true)
				{
					printf("GAME OVER! \n");
					game_over = true;
					break;
				}

			}
		}

		// TODO: Without the for loop the red block goes over player render up the player can hold up block
		// TODO: Remove for loop and if so red block goes over
		// Find better solution

		// Moves every block on the board and for the renderer
		for (int i = 0; i < m_blocks.size(); i++)
		{
			// Check if block is one position above player
			if (m_blocks.at(i).getX() == m_player.getCurrentX() && m_blocks.at(i).getY() + 32 == m_player.getCurrentY())
			{
				printf("Player holds up block \n");
			}
			else
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
		// int spawn_pos2 = (((rand() % 20)) * globals::BLOCK_SIZE) + (globals::SCREEN_HEIGHT / 2 - globals::BLOCK_SIZE * 5);

		printf("spawn pos: %d \n", spawn_pos);

		// Makes a new block in the m_block vector
		m_blocks.push_back(Block(spawn_pos, 0));

		// Creates the block on the board
		m_board[spawn_pos / globals::BLOCK_SIZE][0] = true;
	}
}

void Game::restart()
{
	m_blocks.clear();

	// Reset m_board 
	for (int i = 0; i < globals::SCREEN_WIDTH / globals::BLOCK_SIZE; i++)
	{
		for (int j = 0; j < globals::SCREEN_HEIGHT / globals::BLOCK_SIZE; j++)
		{
			m_board[i][j] = false;
		}

	}

	m_player.move_to_spawn();	

	this->draw(m_renderer);
}

void Game::draw(SDL_Renderer *renderer)
{
	// Color the background black
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0xfff);

	// Clear the renderer
	SDL_RenderClear(m_renderer);

	// m_level.draw(m_renderer);

	// Draw the player object in the backbuffer
	m_player.draw(m_renderer);

	for (int i = 0; i < m_blocks.size(); i++)
	{
		m_blocks.at(i).draw(m_renderer);
	}
	

	//Flip backbuffer and frontbuffer 
	SDL_RenderPresent(m_renderer);
}