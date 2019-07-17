#include "Game.h"

#include <algorithm>



Game::Game():
	m_window(NULL),
	m_screenSurface(NULL),
	time_block_falling(SDL_GetTicks()),
	game_over(false)
{

	//Initialize SDL
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		// Gameloop that runs indefenently
		gameLoop();
	}

}

Game::~Game()
{
	m_ui.~UI();

	// Destroy renderer
	SDL_DestroyRenderer(m_renderer);
	m_renderer = NULL;

	// Destroy window
	SDL_DestroyWindow(m_window);
	m_window = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::gameLoop()
{
	Input input;

	UI m_ui;

	// Spawns the player at position (x,y)
	m_player = Player(globals::PLAYER_SPAWN_X, globals::PLAYER_SPAWN_Y);

	Level m_level;

	SDL_Event event;
	
	// Initialize random seed so rand is not the same every time
	srand(time(NULL));

	//m_level = Level();

	Uint32 time_since_last_frame = SDL_GetTicks();

	Uint32 time_last_move = SDL_GetTicks();

	while (true)
	{
		// Endless loop while the window is not x-d out or escape
		while (!game_over)
		{
			// Movement tick
			Uint32 time_elapsed_move = SDL_GetTicks();

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
						this->~Game();
						return;
					}
				}

				if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
					this->~Game();
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


			float time_elapsed = SDL_GetTicks();
			
			if (time_elapsed - time_since_last_frame > 1000 / globals::FRAME_RATE)
			{

				// Frame rate to be sent to UI
				float frame_rate = 1000 / (time_elapsed - time_since_last_frame);
				// printf("Time elapsed: %.2f, time since last frame: %.2f, frame rate: %.4f \n", time_elapsed, time_since_last_frame, 1000 / (time_elapsed - time_since_last_frame));

				this->update();

				this->draw(m_renderer, frame_rate);

				time_since_last_frame = SDL_GetTicks();
			}

		}

		// Freezes the current renderer
		// 0 in frame_rate argument as gameplay is frozen
		this->draw(m_renderer, 0);

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
				system("CLS");
				printf("New game! \n");
				game_over = false;
			}

		}

		// Keep timers updated
		time_since_last_frame = SDL_GetTicks();
		time_last_move = SDL_GetTicks();
		time_block_falling = SDL_GetTicks();

		// Implement restart function for game
		this->restart();
	}
}

void Game::update()
{
	// The players change in position (in block size chuncks) 
	int dx = (m_player.getCurrentX() - m_player.getPrevX()) / globals::BLOCK_SIZE;
	int dy = (m_player.getCurrentY() - m_player.getPrevY()) / globals::BLOCK_SIZE;

	if (!m_level.check_possible_move(m_player.getCurrentX(), m_player.getCurrentY(), dx, dy))
	{
		m_player.move(-dx, -dy);
	}

	// Moves block every block down every second and spawns a new block
	if (SDL_GetTicks() > time_block_falling)
	{
		time_block_falling += 1000;

		if (m_level.game_over_check(m_player.getCurrentX(), m_player.getCurrentY()))
		{
			game_over = true;
		}

		m_level.update(m_player.getCurrentX(), m_player.getCurrentY());
	}
}

void Game::restart()
{

	m_level.reset_board();

	m_player.move_to_spawn();	

	this->draw(m_renderer, 0);
}

void Game::draw(SDL_Renderer *renderer, float frame_rate)
{

	// Color the background black
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0xfff);

	// Clear the renderer
	SDL_RenderClear(m_renderer);

	
	if(!game_over)
	{
		// Draw the player object in the backbuffer
		m_player.draw(m_renderer);
	}
	else
	{
		m_player.DrawDeathBlock(m_renderer);
	}

	m_level.draw(m_renderer);

	m_ui.drawFPS(m_renderer, frame_rate);

	if (game_over)
	{
		m_ui.drawRestartScreen(m_renderer);
	}

	//Flip backbuffer and frontbuffer 
	SDL_RenderPresent(m_renderer);
}



bool Game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		m_window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (m_window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (m_renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

