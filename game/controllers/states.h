#ifndef STATES_H
#define STATES_H

#include "SDL.h"
#include "../domain/entities/game.h"
#include "../domain/entities/leaderboard.h"
#include "../views/layout/layout.h"

typedef enum {
    MENU_SCREEN,
    GAME_SCREEN,
    LEADERBOARD_SCREEN
} StateScreen;

typedef struct GameState {
    void (*handle_event)(const struct GameState*, SDL_Event*);
    void (*update)(const struct GameState*);
    void (*render)(const struct GameState*, SDL_Renderer*);
    void (*destroy)(const struct GameState*);
} GameState;

typedef struct BoardController BoardController;
typedef struct MenuController MenuController;
typedef struct LeaderBoardController LeaderBoardController;

typedef struct GameScreenState {
    GameState base;
    BoardController* controller;
} GameScreenState;

typedef struct MenuScreenState {
    GameState base;
    MenuController* controller;
} MenuScreenState;

typedef struct LeaderBoardScreenState {
    GameState base;
    LeaderBoardController* controller;
} LeaderBoardScreenState;

GameState* init_game_state(WindowLayout, Game*, void (*)(StateScreen));
GameState* init_menu_state(WindowLayout, void (*)(StateScreen));
GameState* init_leaderboard_state(WindowLayout, LeaderBoard*, void (*)(StateScreen));

#endif //STATES_H
