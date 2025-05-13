#ifndef VIEWS_H
#define VIEWS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>
#include "../layout/layout.h"
#include "../../domain/entities/game.h"

void draw_board(SDL_Renderer*, Game, WindowLayout);
void draw_restart_button(SDL_Renderer*, WindowLayout);
void draw_win_way(SDL_Renderer*, uint16_t, WindowLayout);

#endif //VIEWS_H
