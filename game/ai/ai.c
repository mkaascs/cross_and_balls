#include "ai.h"
#include <stdlib.h>

#define DIFFICULT 5

static const uint16_t WIN_PATTERNS[] = {
    0b111000000, 0b000111000, 0b000000111,
    0b100100100, 0b010010010, 0b001001001,
    0b100010001, 0b001010100
};

static int find_winning_move(uint16_t player_mask, uint16_t empty_mask) {
    for (int i = 0; i < 8; i++) {
        uint16_t win = WIN_PATTERNS[i];
        if (__builtin_popcount(player_mask & win) == 2) {
            uint16_t pos = win & empty_mask;
            if (__builtin_popcount(pos) == 1) {
                for (int j = 0; j < 9; j++)
                    if (pos & (1 << j))
                        return j;
            }
        }
    }

    return -1;
}

static bool is_empty(Game* game, int pos) {
    uint16_t mask = (1 << pos);
    return !(game->crosses_moves & mask) && !(game->balls_moves & mask);
}

void make_move_ai(Game* game) {
    if (game == NULL || game->is_complete)
        return;

    uint16_t bot_moves = game->last_move == Ball ? game->crosses_moves : game->balls_moves;
    uint16_t human_moves = game->last_move == Ball ? game->balls_moves : game->crosses_moves;
    uint16_t empty = ~(bot_moves | human_moves) & 0x1FF;

    int move = -1;
    bool skip_move = (rand() % DIFFICULT == 0);

    move = find_winning_move(bot_moves, empty);
    if (move >= 0 && !skip_move) { game->make_move(game, move); return; }

    move = find_winning_move(human_moves, empty);
    if (move >= 0 && !skip_move) { game->make_move(game, move); return; }

    if (is_empty(game, 4)) { game->make_move(game, 4); return; }

    int corners[] = {0, 2, 6, 8};
    for (int i = 0; i < 4; i++) {
        if (is_empty(game, corners[i])) {
            game->make_move(game, corners[i]);
            return;
        }
    }

    for (int i = 0; i < 9; i++) {
        if (is_empty(game, i)) {
            game->make_move(game, i);
            return;
        }
    }
}