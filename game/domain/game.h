#ifndef GAME_H
#define GAME_H
#include <stdbool.h>
#include <stdint.h>
#include "query/moves.h"

#define MAX_MOVES_COUNT 3

typedef enum {
    Ball, Cross
} Player;

typedef struct Game {
    Player last_move;
    uint16_t balls_moves;
    uint16_t crosses_moves;
    bool is_complete;

    MoveQuery* crosses;
    MoveQuery* balls;

    bool (*check_win)(struct Game* this);
    bool (*check_draw)(struct Game* this);
    bool (*make_move)(struct Game* this, int position);
    uint16_t (*get_win_way)(struct Game* this);
    void (*reset)(struct Game* this);
} Game;

Game* init_game();
void free_game(Game** game);

#endif //GAME_H
