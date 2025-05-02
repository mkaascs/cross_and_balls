#ifndef GAME_H
#define GAME_H
#include <stdbool.h>
#include <stdint.h>

#define BOARD_SIZE 3

typedef enum {
    Ball, Cross
} Player;

typedef struct {
    Player lastMove;
    uint16_t ballsMoves;
    uint16_t crossesMoves;

    bool (*checkWin)();
    bool (*makeMove)(int position);
} Game;

void run_game(Game*);

#endif //GAME_H
