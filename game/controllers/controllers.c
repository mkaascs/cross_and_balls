#include <stdlib.h>
#include <stdio.h>
#include "controllers.h"

int get_position(WindowSize size, int x, int y) {
    int left = (size.window_width - size.cell_size * 3) / 2;
    int top = (size.window_height - size.cell_size * 3) / 2;

    if (x < left || x > 3 * size.cell_size + left ||
        y < top || y > 3 * size.cell_size + top)
        return -1;

    return (y - top) / size.cell_size * 3 + (x - left) / size.cell_size;
}

void on_click(BoardController* this, int x, int y) {
    int position = get_position(this->size, x, y);
    if (position == -1)
        return;

    if (!this->game->make_move(this->game, position))
        return;

    printf("%s: Clicked on %d\n", this->game->lastMove == Cross ? "Cross" : "Ball", position);
    if (this->game->check_win(this->game))
        printf("%s won!", this->game->lastMove == Cross ? "Cross" : "Ball");
}

void on_restart(BoardController* this) {
    this->game->reset(this->game);
}

BoardController* init_controller(WindowSize size, Game* game) {
    BoardController* controller = malloc(sizeof(BoardController));
    controller->game = game;
    controller->size = size;
    controller->on_click = on_click;
    controller->on_restart = on_restart;

    return controller;
}