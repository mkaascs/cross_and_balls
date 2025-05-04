#ifndef BOARD_CONTROLLER_H
#define BOARD_CONTROLLER_H

#include <SDL_render.h>

#include "../domain/game.h"
#include "../views/layout/layout.h"

typedef struct BoardController {
    Game* game;
    WindowLayout layout;
    SDL_Renderer* renderer;
    void (*on_update)(const struct BoardController* this);
    void (*on_click)(const struct BoardController* this, int x, int y);
} BoardController;

typedef struct MainController {
    Game* game;
    WindowLayout layout;
    SDL_Renderer* renderer;
    void (*on_restart_button_click)(const struct MainController* this, int x, int y);
} MainController;

BoardController* init_board_controller(SDL_Renderer*, WindowLayout, Game*);
MainController* init_main_controller(SDL_Renderer*, WindowLayout, Game*);

#endif //BOARD_CONTROLLER_H
