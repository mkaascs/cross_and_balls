#ifndef GAME_H
#define GAME_H
#include <stdbool.h>
#include <stdint.h>

#define BOARD_SIZE 3

typedef enum {
    Ball, Cross
} Player;

typedef struct Game {
    Player lastMove;
    uint16_t ballsMoves;
    uint16_t crossesMoves;
    bool is_complete;

    bool (*check_win)(struct Game* this);
    bool (*make_move)(struct Game* this, int position);
    void (*reset)(struct Game* this);
} Game;

Game* init_game();

#endif //GAME_H
