#ifndef BOARD_CONTROLLER_H
#define BOARD_CONTROLLER_H

#include <SDL_render.h>

#include "../domain/game.h"
#include "../views/window/size.h"

typedef struct BoardController {
    Game* game;
    WindowSize size;
    SDL_Renderer* renderer;
    void (*on_click)(const struct BoardController* this, int x, int y);
    void (*on_restart)(const struct BoardController* this);
} BoardController;

BoardController* init_controller(SDL_Renderer*, WindowSize, Game*);

#endif //BOARD_CONTROLLER_H
