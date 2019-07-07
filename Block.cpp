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

void Block::draw(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);

	SDL_Rect rect{ m_x, m_y, globals::BLOCK_SIZE, globals::BLOCK_SIZE };
	SDL_RenderFillRect(renderer, &rect);
}
