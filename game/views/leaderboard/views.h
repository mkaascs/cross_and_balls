#ifndef VIEWS_H
#define VIEWS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>
#include "../layout/layout.h"
#include "../../domain/entities/leaderboard.h"

void draw_leaderboard(SDL_Renderer*, LeaderBoard, WindowLayout);

#endif //VIEWS_H
