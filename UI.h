#ifndef UI_H
#define UI_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

#include "Globals.h"

class UI
{

public:

	UI();

	~UI();

	// Loads given font
	void loadFont(const char *file_name, int font_size);

	// Renders the UI
	void drawFont(SDL_Renderer *renderer, std::string text, int x, int y, float scale_factor);

	void drawFPS(SDL_Renderer *renderer, float frame_rate);

	void drawRestartScreen(SDL_Renderer *renderer);

private:
	TTF_Font *m_font;



};


#endif // !UI_H
