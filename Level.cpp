#include "Level.h"

Level::Level()
{

}


Level::~Level()
{
}


void Level::draw(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

	SDL_Rect rect{ 0, 0, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT };
}

