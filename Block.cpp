#include "Block.h"


Block::Block()
{

}

Block::Block(int x, int y, states state) :
	m_x(x),
	m_y(y),
	m_state(state)
{

}

void Block::SpawnBlock(int x, int y)
{
	this->m_x = x;
	this->m_y = y;
	this->m_state = FREE;
}

Block::~Block()
{

}

void Block::move(int dx, int dy)
{
	this->m_x += dx * globals::BLOCK_SIZE;
	this->m_y += dy * globals::BLOCK_SIZE;
}


int Block::getX()
{
	return this->m_x;
}

int Block::getY()
{
	return this->m_y;
}

void Block::ChangeState(states state)
{
	this->m_state = state;
}

states Block::GetState()
{
	return this->m_state;
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

	SDL_Rect rect{ this->m_x, this->m_y, globals::BLOCK_SIZE, globals::BLOCK_SIZE };
	SDL_RenderFillRect(renderer, &rect);
}
