#ifndef STATES_H
#define STATES_H

#include "SDL.h"
#include "../domain/entities/game.h"
#include "../domain/entities/leaderboard.h"
#include "../views/layout/layout.h"

typedef enum {
    MENU_SCREEN,
    MODE_SCREEN,
    GAME_SCREEN,
    LEADERBOARD_SCREEN,
    STATE_SCREEN_COUNT
} StateScreen;

typedef struct GameState {
    void (*handle_event)(const struct GameState*, SDL_Event*);
    void (*update)(const struct GameState*);
    void (*render)(const struct GameState*, SDL_Renderer*);
    void (*destroy)(const struct GameState*);
} GameState;

typedef struct BoardController BoardController;
typedef struct MenuController MenuController;
typedef struct LeaderboardController LeaderboardController;
typedef struct ModeController ModeController;

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
    LeaderboardController* controller;
} LeaderboardScreenState;

typedef struct ModeScreenState {
    GameState base;
    ModeController* controller;
} ModeScreenState;

GameState* init_game_state(WindowLayout, Game*, LeaderBoard*, void (*)(StateScreen));
GameState* init_menu_state(WindowLayout, void (*)(StateScreen));
GameState* init_leaderboard_state(WindowLayout, LeaderBoard*, void (*)(StateScreen));
GameState* init_mode_state(WindowLayout, void (*)(StateScreen));

#endif //STATES_H
