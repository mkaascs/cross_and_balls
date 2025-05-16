#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "SDL.h"
#include <SDL_ttf.h>
#include "../layout/layout.h"

void draw_close_button(SDL_Renderer* renderer, WindowLayout layout);
void draw_text(SDL_Renderer* renderer, const char* text, int x, int y, int font_size, SDL_Color color);
void draw_text_centred_x(SDL_Renderer* renderer, const char* text, int rect_width, int y, int font_size, SDL_Color);

#endif // PRIMITIVES_H
