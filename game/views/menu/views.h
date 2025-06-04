#ifndef VIEWS_H
#define VIEWS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>
#include "../layout/layout.h"
#include "../components/input_box.h"

void draw_menu(SDL_Renderer*, WindowLayout, InputBox);

#endif //VIEWS_H
