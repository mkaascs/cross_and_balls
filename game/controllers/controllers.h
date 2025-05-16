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

typedef struct LeaderboardController {
    WindowLayout layout;
    LeaderBoard* leader_board;

    void (*on_update)(const LeaderboardController*, SDL_Renderer*);
    void (*on_click)(const LeaderboardController*, int, int);

    void (*change_state)(StateScreen);
} LeaderboardController;

BoardController* init_board_controller(WindowLayout, Game*, void (*)(StateScreen));
MenuController* init_menu_controller(WindowLayout, void (*)(StateScreen));
LeaderboardController* init_leaderboard_controller(WindowLayout, LeaderBoard*, void (*)(StateScreen));

#endif //BOARD_CONTROLLER_H
