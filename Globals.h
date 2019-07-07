#ifndef GLOBALS_H
#define GLOBALS_H

namespace globals
{
	// Size of created screen
	const int SCREEN_WIDTH = 1280; //640;
	const int SCREEN_HEIGHT = 960; // 480;

	const int BLOCK_SIZE = 32;

	const int FRAME_RATE = 60;

	const int MOVEMENT_TICK = 100;

	const int PLAYER_SPAWN_X = SCREEN_WIDTH / 2;
	const int PLAYER_SPAWN_Y = BLOCK_SIZE * 4;
}

#endif // !GLOBALS_H
