#include "../controllers.h"
#include "../../views/leaderboard/views.h"
#include "../../../memstat/memstat.h"

static void on_update(const LeaderboardController* this, SDL_Renderer* renderer) {
    draw_leaderboard(renderer, *this->leader_board, this->layout);
}

static void on_close_button_click(const LeaderboardController* this) {
    this->change_state(MENU_SCREEN);
}

static void on_click(const LeaderboardController* this, int x, int y) {
    if (x >= this->layout.close_button_x && x <= this->layout.close_button_x + this->layout.close_button_width &&
        y >= this->layout.close_button_y && y <= this->layout.close_button_y + this->layout.close_button_height) {
        on_close_button_click(this);
        }
}

LeaderboardController* init_leaderboard_controller(WindowLayout layout, LeaderBoard* leaderboard, void (*change_state)(StateScreen)) {
    LeaderboardController* controller = track_malloc(sizeof(LeaderboardController));
    controller->change_state = change_state;
    controller->leader_board = leaderboard;
    controller->layout = layout;
    controller->on_click = on_click;
    controller->on_update = on_update;

    return controller;
}