#include "Block.h"


Block::Block()
{

}

Block::Block(int x, int y) :
	m_x(x),
	m_y(y)
{

}

Block::~Block()
{

}

void Block::move(int dx, int dy)
{
	m_x += dx * globals::BLOCK_SIZE;
	m_y += dy * globals::BLOCK_SIZE;
}


int Block::getX()
{
	return m_x;
}

int Block::getY()
{
	return m_y;
}

void Block::draw(SDL_Renderer *renderer, enum colors color)
{
	// Choose correct RenderDrawColor
	switch (color)
	{
	case BLACK:
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		break;
	case RED:
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		break;
	case GREEN:
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		break;
	case BLUE:
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		break;
	case CYAN:
		SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
		break;
	case MAGENTA:
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
		break;
	case YELLOW:
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
		break;
	case WHITE:
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		break;
	}

	SDL_Rect rect{ m_x, m_y, globals::BLOCK_SIZE, globals::BLOCK_SIZE };
	SDL_RenderFillRect(renderer, &rect);
}
