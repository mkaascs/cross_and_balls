#include "../controllers.h"
#include "../../views/leaderboard/views.h"
#include "../../../memstat/memstat.h"

static void on_update(const LeaderBoardController* this, SDL_Renderer* renderer) {
    draw_leader_board(renderer, *this->leader_board, this->layout);
}

static void on_close_button_click(const LeaderBoardController* this) {
    this->change_state(MENU_SCREEN);
}

static void on_click(const LeaderBoardController* this, int x, int y) {
    if (x >= this->layout.close_button_x && x <= this->layout.close_button_x + this->layout.close_button_width &&
        y >= this->layout.close_button_y && y <= this->layout.close_button_y + this->layout.close_button_height) {
        on_close_button_click(this);
        }
}

LeaderBoardController* init_leader_board_controller(WindowLayout layout, LeaderBoard* leader_board, void (*change_state)(StateScreen)) {
    LeaderBoardController* controller = track_malloc(sizeof(LeaderBoardController));
    controller->change_state = change_state;
    controller->leader_board = leader_board;
    controller->layout = layout;
    controller->on_click = on_click;
    controller->on_update = on_update;

    return controller;
}