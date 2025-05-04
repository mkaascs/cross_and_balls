#include <stdlib.h>
#include <stdio.h>
#include "controllers.h"

#include "../views/views.h"

int get_position(WindowLayout layout, int x, int y) {
    if (x < layout.cell_left || x > 3 * layout.cell_size + layout.cell_left ||
        y < layout.cell_top || y > 3 * layout.cell_size + layout.cell_top)
        return -1;

    return (y - layout.cell_top) / layout.cell_size * 3 + (x - layout.cell_left) / layout.cell_size;
}

void on_update(const BoardController* this) {
    draw_board(this->renderer, *this->game, this->layout);
    if (this->game->is_complete) {
        draw_restart_button(this->renderer, this->layout);
        draw_win_way(this->renderer, this->game->get_win_way(this->game), this->layout);
    }
}

void on_click(const BoardController* this, int x, int y) {
    int position = get_position(this->layout, x, y);
    if (position == -1)
        return;

    if (!this->game->make_move(this->game, position))
        return;

    printf("%s: Clicked on %d\n", this->game->last_move == Cross ? "Cross" : "Ball", position);
    if (this->game->check_win(this->game)) {
        printf("%s won!", this->game->last_move == Cross ? "Cross" : "Ball");
    }

    if (this->game->check_draw(this->game)) {
        printf("Nobody won!");
    }
}

void on_restart_button_click(const MainController* this, int x, int y) {
    if (x < this->layout.restart_button_x || x > this->layout.restart_button_x + this->layout.restart_button_width ||
        y < this->layout.restart_button_y || y > this->layout.restart_button_y + this->layout.restart_button_height)
        return;

    this->game->reset(this->game);
}

BoardController* init_board_controller(SDL_Renderer* renderer, WindowLayout layout, Game* game) {
    BoardController* controller = malloc(sizeof(BoardController));
    controller->game = game;
    controller->layout = layout;
    controller->renderer = renderer;
    controller->on_click = on_click;
    controller->on_update = on_update;

    return controller;
}

MainController* init_main_controller(SDL_Renderer* renderer, WindowLayout layout, Game* game) {
    MainController* controller = malloc(sizeof(MainController));
    controller->game = game;
    controller->layout = layout;
    controller->renderer = renderer;
    controller->on_restart_button_click = on_restart_button_click;
    return controller;
}