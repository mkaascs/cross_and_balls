#ifndef VIEW_H
#define VIEW_H

#include <SDL.h>
#include "../game.h"
#include "../config/config.h"

void draw_board(SDL_Renderer*, Game, WindowConfig);

#endif //VIEW_H
