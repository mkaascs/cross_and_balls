#include <stdlib.h>
#include "game.h"

#define WIN_PATTERNS_COUNT 8

const uint16_t WIN_PATTERNS[WIN_PATTERNS_COUNT] = {
    0b111000000, 0b000111000, 0b000000111,
    0b100100100, 0b010010010, 0b001001001,
    0b100010001, 0b001010100
};

bool check_win(Game* this) {
    uint16_t current_player = this->lastMove == Cross
        ? this->crossesMoves
        : this->ballsMoves;

    for (int index = 0; index < WIN_PATTERNS_COUNT; index++) {
        if ((current_player & WIN_PATTERNS[index]) == WIN_PATTERNS[index]) {
            this->is_complete = true;
            return true;
        }
    }

    return false;
}

bool make_move(Game* this, int position) {
    if (this->is_complete)
        return false;

    if (position < 0 || position > 8)
        return false;

    uint16_t mask = 1 << position;
    if ((this->crossesMoves | this->ballsMoves) & mask)
        return false;

    if (this->lastMove == Cross)
        this->ballsMoves |= mask;

    else this->crossesMoves |= mask;

    this->lastMove = !this->lastMove;
    return true;
}

void reset(Game* this) {
    this->crossesMoves = 0;
    this->ballsMoves = 0;
    this->lastMove = Ball;
    this->is_complete = false;
}

Game* init_game() {
    Game* new_game = malloc(sizeof(Game));
    new_game->lastMove = Ball;

    new_game->crossesMoves = 0;
    new_game->ballsMoves = 0;
    new_game->is_complete = false;

    new_game->check_win = check_win;
    new_game->make_move = make_move;
    return new_game;
}