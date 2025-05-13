#ifndef BOARD_CONTROLLER_H
#define BOARD_CONTROLLER_H

#include <SDL_render.h>

#include "states.h"
#include "../domain/entities/game.h"
#include "../domain/entities/leaderboard.h"
#include "../views/layout/layout.h"

typedef struct BoardController {
    Game* game;
    WindowLayout layout;

    void (*on_update)(const BoardController*, SDL_Renderer*);
    void (*on_click)(const BoardController*, int, int);

    void (*change_state)(StateScreen);
} BoardController;

typedef struct MenuController {
    WindowLayout layout;

    void (*on_update)(const MenuController*, SDL_Renderer*);
    void (*on_click)(const MenuController*, int, int);

    void (*change_state)(StateScreen);
} MenuController;

typedef struct LeaderBoardController {
    WindowLayout layout;
    LeaderBoard* leader_board;

    void (*on_update)(const LeaderBoardController*, SDL_Renderer*);
    void (*on_click)(const LeaderBoardController*, int, int);

    void (*change_state)(StateScreen);
} LeaderBoardController;

BoardController* init_board_controller(WindowLayout, Game*, void (*)(StateScreen));
MenuController* init_menu_controller(WindowLayout, void (*)(StateScreen));
LeaderBoardController* init_leader_board_controller(WindowLayout, LeaderBoard*, void (*)(StateScreen));

#endif //BOARD_CONTROLLER_H
