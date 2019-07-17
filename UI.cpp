#include "UI.h"


UI::UI()
{
	this->m_font = NULL;
}

UI::~UI()
{
	//Free global font
	if (!m_font)
	{
		TTF_CloseFont(m_font);
		this->m_font = NULL;
	}


	//Free loaded images
	//m_text_texture.free();

	//Free global font
	//TTF_CloseFont(m_font);
	//m_font = NULL;

}



void UI::loadFont(const char *file_name, int font_size)
{
	this->m_font = TTF_OpenFont(file_name, font_size);

	if (!m_font)
	{
		printf("TTF_OpenFont: %s\n", TTF_GetError());
	}
}

void UI::drawFont(SDL_Renderer *renderer, std::string text, int x, int y, float scale_factor)
{
	// Load the font
	loadFont("SF Old Republic.ttf", 72);

	SDL_Color color = { 255, 255, 255 };

	SDL_Surface *surface_message = TTF_RenderText_Solid(this->m_font, text.c_str(), color);

	SDL_Texture *message = SDL_CreateTextureFromSurface(renderer, surface_message);

	// Queary width and height of SDL_Texture
	int texture_height, texture_width;
	SDL_QueryTexture(message, NULL, NULL, &texture_width, &texture_height);

	SDL_Rect message_rect; //create a rect
	message_rect.x = x;  //controls the rect's x coordinate 
	message_rect.y = y; // controls the rect's y coordinte
	message_rect.w = texture_width * scale_factor; // controls the width of the rect
	message_rect.h = texture_height * scale_factor; // controls the height of the rect

	SDL_RenderCopy(renderer, message, NULL, &message_rect);

	m_font = NULL;
	SDL_FreeSurface(surface_message);
	SDL_DestroyTexture(message);

}


void UI::drawFPS(SDL_Renderer *renderer, float frame_rate)
{

	std::string text = "FPS: "  + std::to_string(std::lround(frame_rate));

	drawFont(renderer, text, 10, 10, 0.25);
}

void UI::drawRestartScreen(SDL_Renderer *renderer)
{
	loadFont("SF Old Republic.ttf", 72);

	std::string text_top = "Press Space Bar";
	std::string text_bottom = "to Play Again!";

	drawFont(renderer, text_top, (globals::SCREEN_WIDTH )  / 4, globals::SCREEN_HEIGHT / 2, 1);
	drawFont(renderer, text_bottom, (globals::SCREEN_WIDTH )  / 4, (globals::SCREEN_HEIGHT + 120) / 2, 1);

}