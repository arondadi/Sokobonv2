#ifndef LEVEL_H
#define LEVEL_H

#include <SDL.h>

#include "Globals.h"

class Level
{
public:
	Level();
	~Level();

	void draw(SDL_Renderer *renderer);
};

#endif // !LEVEL_H
