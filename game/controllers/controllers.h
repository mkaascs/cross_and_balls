#ifndef BOARD_CONTROLLER_H
#define BOARD_CONTROLLER_H

#include <SDL_render.h>

#include "states.h"
#include "../domain/entities/game.h"
#include "../domain/entities/leaderboard.h"
#include "../views/layout/layout.h"
#include "../views/components/input_box.h"

typedef struct BoardController {
    Game* game;
    LeaderBoard* leader_board;
    WindowLayout layout;

    void (*on_update)(const BoardController*, SDL_Renderer*);
    void (*on_click)(const BoardController*, int, int);

    void (*change_state)(StateScreen);
} BoardController;

typedef struct MenuController {
    WindowLayout layout;
    InputBox input_box;

    void (*on_update)(const MenuController*, SDL_Renderer*);
    void (*on_click)(const MenuController*, int, int);
    void (*on_text_input)(MenuController*, const SDL_Event*);

    void (*change_state)(StateScreen);
} MenuController;

typedef struct ModeController {
    WindowLayout layout;

    void (*on_update)(const ModeController*, SDL_Renderer*);
    void (*on_click)(const ModeController*, int, int);

    void (*change_state)(StateScreen);
} ModeController;

typedef struct LeaderboardController {
    WindowLayout layout;
    LeaderBoard* leader_board;

    void (*on_update)(const LeaderboardController*, SDL_Renderer*);
    void (*on_click)(const LeaderboardController*, int, int);

    void (*change_state)(StateScreen);
} LeaderboardController;

BoardController* init_board_controller(WindowLayout, Game*, LeaderBoard*, void (*)(StateScreen));
MenuController* init_menu_controller(WindowLayout, void (*)(StateScreen));
ModeController* init_mode_controller(WindowLayout, void (*)(StateScreen));
LeaderboardController* init_leaderboard_controller(WindowLayout, LeaderBoard*, void (*)(StateScreen));

#endif //BOARD_CONTROLLER_H
