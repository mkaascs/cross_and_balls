#ifndef VIEWS_H
#define VIEWS_H

#include <SDL.h>
#include "window/size.h"
#include "../domain/game.h"

void free_sprites();
bool load_sprites(SDL_Renderer*);

void draw_board(SDL_Renderer*, Game, WindowSize);
void draw_cross(SDL_Renderer*, SDL_Rect*);
void draw_ball(SDL_Renderer*, SDL_Rect*);

#endif //VIEWS_H
