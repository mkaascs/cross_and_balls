#ifndef VIEWS_H
#define VIEWS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>
#include "../layout/layout.h"

void draw_menu(SDL_Renderer*, WindowLayout);
void handle_input_box_event(SDL_Event*, char*);
void init_menu_view(WindowLayout);

#endif //VIEWS_H
