#ifndef GAME_H
#define GAME_H
#include <stdbool.h>
#include <stdint.h>
#include "../query/moves.h"

#define MAX_MOVES_COUNT 3

typedef enum {
    Ball, Cross
} Player;

typedef struct {
    unsigned int cross_score;
    unsigned int ball_score;
} GameScore;

typedef struct Game {
    Player last_move;
    uint16_t balls_moves;
    uint16_t crosses_moves;
    bool is_complete;

    MoveQuery* crosses;
    MoveQuery* balls;

    bool (*check_win)(struct Game*);
    bool (*check_draw)(struct Game*);
    bool (*make_move)(struct Game*, int);
    uint16_t (*get_win_way)(struct Game*);
    void (*reset)(struct Game*);
} Game;

Game* init_game();
void free_game(Game*);

#endif //GAME_H
