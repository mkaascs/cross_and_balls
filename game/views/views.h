#ifndef VIEWS_H
#define VIEWS_H

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "layout/layout.h"
#include "../domain/game.h"

void draw_board(SDL_Renderer*, Game, WindowLayout);

void draw_text(SDL_Renderer*, int, int, const char*);

void draw_restart_button(SDL_Renderer*, WindowLayout);

void free_sprites();
bool load_sprites(SDL_Renderer*);

void draw_cross(SDL_Renderer*, const SDL_Rect*);
void draw_ball(SDL_Renderer*, const SDL_Rect*);

void draw_win_way(SDL_Renderer*, uint16_t, WindowLayout);

#endif //VIEWS_H
