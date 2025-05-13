#include <stdlib.h>
#include "game.h"

#include "../../../memstat/memstat.h"

#define WIN_PATTERNS_COUNT 8

static const uint16_t WIN_PATTERNS[WIN_PATTERNS_COUNT] = {
    0b111000000, 0b000111000, 0b000000111,
    0b100100100, 0b010010010, 0b001001001,
    0b100010001, 0b001010100
};

static bool check_win(Game* this) {
    if (this == NULL)
        return false;

    uint16_t current_player = this->last_move == Cross
        ? this->crosses_moves
        : this->balls_moves;

    for (int index = 0; index < WIN_PATTERNS_COUNT; index++) {
        if ((current_player & WIN_PATTERNS[index]) == WIN_PATTERNS[index]) {
            this->is_complete = true;
            return true;
        }
    }

    return false;
}

static bool check_draw(Game* this) {
    uint16_t occupied = this->crosses_moves | this->balls_moves;
    bool full = (occupied & 0x1FF) == 0x1FF;
    bool no_winner = !check_win(this);
    if (!(full && no_winner))
        return false;

    this->is_complete = true;
    return true;
}

static bool make_move(Game* this, int position) {
    if (this == NULL)
        return false;

    if (this->is_complete)
        return false;

    if (position < 0 || position > 8)
        return false;

    uint16_t mask = 1 << position;
    if ((this->crosses_moves | this->balls_moves) & mask)
        return false;

    MoveElement* move = track_malloc(sizeof(MoveElement));
    move->position = position;
    move->next = NULL;

    if (this->last_move == Cross) {
        this->balls_moves |= mask;
        push(this->balls, move);
    }

    else {
        this->crosses_moves |= mask;
        push(this->crosses, move);
    }

    this->last_move = !this->last_move;
    if (this->crosses->length <= MAX_MOVES_COUNT && this->balls->length <= MAX_MOVES_COUNT)
        return true;

    MoveElement* last_move;

    if (this->crosses->length > MAX_MOVES_COUNT) {
        last_move = pop(this->crosses);
        this->crosses_moves &= ~(1 << last_move->position);
    }

    else {
        last_move = pop(this->balls);
        this->balls_moves &= ~(1 << last_move->position);
    }

    track_free((void**)&last_move);
    return true;
}

static uint16_t get_win_way(Game* this) {
    if (this == NULL)
        return 0;

    uint16_t current_player = this->last_move == Cross
        ? this->crosses_moves
        : this->balls_moves;

    for (int index = 0; index < WIN_PATTERNS_COUNT; index++)
        if ((current_player & WIN_PATTERNS[index]) == WIN_PATTERNS[index])
            return WIN_PATTERNS[index];

    return 0;
}

static void reset(Game* this) {
    if (this == NULL)
        return;

    this->crosses_moves = 0;
    this->balls_moves = 0;
    this->last_move = Ball;
    this->is_complete = false;
    MoveElement* current = pop(this->balls);
    while (current != NULL) {
        track_free((void**)&current);
        current = pop(this->balls);
    }

    current = pop(this->crosses);
    while (current != NULL) {
        track_free((void**)&current);
        current = pop(this->crosses);
    }
}

Game* init_game() {
    Game* new_game = track_malloc(sizeof(Game));
    new_game->last_move = Ball;

    new_game->crosses_moves = 0;
    new_game->balls_moves = 0;
    new_game->is_complete = false;

    new_game->balls = track_calloc(0, sizeof(MoveQuery));
    new_game->crosses = track_calloc(0, sizeof(MoveQuery));
    new_game->balls->tail = NULL;
    new_game->crosses->tail = NULL;

    new_game->check_win = check_win;
    new_game->check_draw = check_draw;
    new_game->make_move = make_move;
    new_game->get_win_way = get_win_way;
    new_game->reset = reset;
    return new_game;
}

void free_game(Game* game) {
    game->reset(game);
    free_query(game->balls);
    free_query(game->crosses);
    track_free((void**)&game);
}