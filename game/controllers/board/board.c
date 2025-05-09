#include "../controllers.h"
#include "../../../memstat/memstat.h"

#include "../../views/board/views.h"

static int get_position(WindowLayout layout, int x, int y) {
    if (x < layout.cell_left || x > 3 * layout.cell_size + layout.cell_left ||
        y < layout.cell_top || y > 3 * layout.cell_size + layout.cell_top)
        return -1;

    return (y - layout.cell_top) / layout.cell_size * 3 + (x - layout.cell_left) / layout.cell_size;
}

static void on_update(const BoardController* this, SDL_Renderer* renderer) {
    draw_board(renderer, *this->game, this->layout);
    if (this->game->is_complete) {
        draw_restart_button(renderer, this->layout);
        draw_win_way(renderer, this->game->get_win_way(this->game), this->layout);
    }
}

static void on_restart_button_click(const BoardController* this, int x, int y) {
    if (x < this->layout.restart_button_x || x > this->layout.restart_button_x + this->layout.restart_button_width ||
        y < this->layout.restart_button_y || y > this->layout.restart_button_y + this->layout.restart_button_height)
        return;

    this->game->reset(this->game);
}

static void on_click(const BoardController* this, int x, int y) {
    int position = get_position(this->layout, x, y);
    if (position == -1)
        return;

    if (!this->game->make_move(this->game, position))
        return;

    if (this->game->check_win(this->game)) {
        if (this->game->last_move == Cross)
            this->game->score.cross_score++;

        else this->game->score.ball_score++;

        printf("Cross: %d; Ball: %d\n", this->game->score.cross_score, this->game->score.ball_score);
    }

    if (this->game->check_draw(this->game)) {
        printf("Nobody won!\n");
    }
}

BoardController* init_board_controller(SDL_Renderer* renderer, WindowLayout layout, Game* game) {
    BoardController* controller = track_malloc(sizeof(BoardController));
    controller->game = game;
    controller->layout = layout;
    controller->on_click = on_click;
    controller->on_update = on_update;
    controller->on_restart_button_click = on_restart_button_click;

    return controller;
}