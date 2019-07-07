#include "Player.h"


Player::Player()
{

}

Player::Player(int x, int y):
m_currentX(x),
m_currentY(y),
m_prevX(NULL),
m_prevY(NULL)
{

}

Player::~Player()
{

}


void Player::move( int dx, int dy)
{
	m_prevY = m_currentY;
	m_prevX = m_currentX;
	m_currentY += dy * globals::BLOCK_SIZE;
	m_currentX += dx * globals::BLOCK_SIZE;
}

void Player::move_to_spawn()
{
	m_currentX = globals::PLAYER_SPAWN_X;
	m_currentY = globals::PLAYER_SPAWN_Y;
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

void Player::draw(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

	SDL_Rect rect{ m_currentX, m_currentY, globals::BLOCK_SIZE, globals::BLOCK_SIZE };
	SDL_RenderFillRect(renderer, &rect);
}
