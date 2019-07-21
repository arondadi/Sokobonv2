#include "Player.h"


Player::Player()
{

}

Player::Player(int x, int y):
m_currentX(x),
m_currentY(y),
m_prevX(x),
m_prevY(y),
m_up(0), 
m_down(0), 
m_left(0), 
m_right(0),
CurrentFacing(UP)
{

}

Player::~Player()
{

}


void Player::move(int dx, int dy)
{
	if (dx == 1)
	{
		CurrentFacing = RIGHT;
	}
	else if (dx == -1)
	{
		CurrentFacing = LEFT;
	}
	else if (dy == 1)
	{
		CurrentFacing = DOWN;
	}
	else if (dy == -1)
	{
		CurrentFacing = UP;
	}

	m_prevY = m_currentY;
	m_prevX = m_currentX;
	m_currentY += dy * globals::BLOCK_SIZE;
	m_currentX += dx * globals::BLOCK_SIZE;
}

void Player::move_to_spawn()
{
	m_currentX = globals::PLAYER_SPAWN_X;
	m_currentY = globals::PLAYER_SPAWN_Y;
	m_prevY = m_currentY;
	m_prevX = m_currentX;
}


int Player::getCurrentX()
{
	return m_currentX;
}

int Player::getCurrentY()
{
	return m_currentY;
}

int Player::getPrevX()
{
	return m_prevX;
}

int Player::getPrevY()
{
	return m_prevY;
}

facing Player::GetFacing()
{
	return CurrentFacing;
}

void Player::draw(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

	SDL_Rect rect{ m_currentX, m_currentY, globals::BLOCK_SIZE, globals::BLOCK_SIZE };
	SDL_RenderFillRect(renderer, &rect);

	SDL_Rect facingRect{ NULL };

	SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0xff, 0x00);
	switch (this->CurrentFacing)
	{
	case UP:
		facingRect.x = m_currentX;
		facingRect.y = m_currentY;
		facingRect.h = globals::BLOCK_SIZE / 4;
		facingRect.w = globals::BLOCK_SIZE;
		break;
	case DOWN:
		facingRect.x = m_currentX;
		facingRect.y = m_currentY + 24; // Bottom of players rect
		facingRect.h = globals::BLOCK_SIZE / 4;
		facingRect.w = globals::BLOCK_SIZE;
		break;
	case LEFT:
		facingRect.x = m_currentX;
		facingRect.y = m_currentY;
		facingRect.h = globals::BLOCK_SIZE;
		facingRect.w = globals::BLOCK_SIZE / 4;
		break;
	case RIGHT:
		facingRect.x = m_currentX + 24; // Right side of players rect
		facingRect.y = m_currentY;
		facingRect.h = globals::BLOCK_SIZE;
		facingRect.w = globals::BLOCK_SIZE / 4;
		break;
	}

	SDL_RenderFillRect(renderer, &facingRect);
}

void Player::DrawDeathBlock(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Rect rect{ m_currentX - globals::BLOCK_SIZE * 0.1, m_currentY - globals::BLOCK_SIZE * 0.1, globals::BLOCK_SIZE * 1.2 , globals::BLOCK_SIZE * 1.2};
	SDL_RenderFillRect(renderer, &rect);

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	SDL_Rect RectBlock{ m_currentX, m_currentY, globals::BLOCK_SIZE, globals::BLOCK_SIZE };
	SDL_RenderFillRect(renderer, &RectBlock);
	
}