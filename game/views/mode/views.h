#ifndef VIEWS_H
#define VIEWS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>
#include "../layout/layout.h"

#define MODE_BUTTONS_COUNT 4

void draw_mode_choice(SDL_Renderer*, WindowLayout);

#endif //VIEWS_H
