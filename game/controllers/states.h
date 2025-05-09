#ifndef STATES_H
#define STATES_H

#include "SDL.h"
#include "controllers.h"

typedef struct GameState {
    void (*handle_event)(struct GameState* this, SDL_Event* event);
    void (*update)(struct GameState* this);
    void (*render)(struct GameState* this, SDL_Renderer* renderer);
    void (*destroy)(struct GameState* this);
} GameState;

typedef struct GameScreenState {
    GameState base;
    BoardController* controller;
} GameScreenState;

GameState* init_game_state(SDL_Renderer* renderer, WindowLayout layout, Game* game);

#endif //STATES_H
