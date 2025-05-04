#ifndef VIEWS_H
#define VIEWS_H

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "window/size.h"
#include "../domain/game.h"

void draw_board(SDL_Renderer*, Game, WindowSize);

void free_sprites();
bool load_sprites(SDL_Renderer*);

void draw_cross(SDL_Renderer*, const SDL_Rect*);
void draw_ball(SDL_Renderer*, const SDL_Rect*);

void draw_win_way(SDL_Renderer*, uint16_t, WindowSize);

#endif //VIEWS_H
