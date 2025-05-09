#ifndef BOARD_CONTROLLER_H
#define BOARD_CONTROLLER_H

#include <SDL_render.h>

#include "../domain/game.h"
#include "../views/layout/layout.h"

typedef struct BoardController {
    Game* game;
    WindowLayout layout;
    void (*on_update)(const struct BoardController* this, SDL_Renderer* renderer);
    void (*on_click)(const struct BoardController* this, int x, int y);
    void (*on_restart_button_click)(const struct BoardController* this, int x, int y);
} BoardController;

BoardController* init_board_controller(SDL_Renderer*, WindowLayout, Game*);

#endif //BOARD_CONTROLLER_H
