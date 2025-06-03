#ifndef VIEWS_H
#define VIEWS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>
#include "../layout/layout.h"
#include "../../domain/entities/game.h"

void draw_board(SDL_Renderer*, Game, WindowLayout, bool);

#endif //VIEWS_H
