#include "../controllers.h"
#include "../states.h"
#include "../../views/board/views.h"
#include "../../../memstat/memstat.h"

static void on_update(const BoardController* this, SDL_Renderer* renderer) {
    draw_board(renderer, *this->game, this->layout);
    if (this->game->is_complete) {
        draw_restart_button(renderer, this->layout);
        draw_win_way(renderer, this->game->get_win_way(this->game), this->layout);
    }
}

static int get_position(BoardLayout layout, int x, int y) {
    if (x < layout.cell_left || x > 3 * layout.cell_size + layout.cell_left ||
        y < layout.cell_top || y > 3 * layout.cell_size + layout.cell_top)
        return -1;

    return (y - layout.cell_top) / layout.cell_size * 3 + (x - layout.cell_left) / layout.cell_size;
}

static void on_restart_button_click(const BoardController* this) {
    this->game->reset(this->game);
}

static void on_close_button_click(const BoardController* this) {
    this->game->reset(this->game);
    this->change_state(MENU_SCREEN);
}

static void on_click(const BoardController* this, int x, int y) {
    if (x >= this->layout.close_button_x && x <= this->layout.close_button_x + this->layout.close_button_width &&
        y >= this->layout.close_button_y && y <= this->layout.close_button_y + this->layout.close_button_height) {
        on_close_button_click(this);
        return;
    }

    if (this->game->is_complete && x >= this->layout.board.restart_button_x && x <= this->layout.board.restart_button_x + this->layout.board.restart_button_width &&
        y >= this->layout.board.restart_button_y && y <= this->layout.board.restart_button_y + this->layout.board.restart_button_height) {
        on_restart_button_click(this);
        return;
    }

    int position = get_position(this->layout.board, x, y);
    if (position == -1)
        return;

    if (!this->game->make_move(this->game, position))
        return;

    if (this->game->check_win(this->game)) {

    }

    if (this->game->check_draw(this->game)) {
        printf("Nobody won!\n");
    }
}

BoardController* init_board_controller(WindowLayout layout, Game* game, void (*change_state)(StateScreen)) {
    BoardController* controller = track_malloc(sizeof(BoardController));
    controller->change_state = change_state;
    controller->game = game;
    controller->layout = layout;
    controller->on_click = on_click;
    controller->on_update = on_update;

    return controller;
}