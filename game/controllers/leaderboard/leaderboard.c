#include "../controllers.h"
#include "../../views/leaderboard/views.h"
#include "../../../memstat/memstat.h"

static bool is_on_element_click(ElementLayout element, int x, int y) {
    return x >= element.margin_x && x <= element.margin_x + element.width &&
        y >= element.margin_y && y <= element.margin_y + element.height;
}

static void on_close_button_click(const LeaderboardController* this) {
    this->change_state(MENU_SCREEN);
}

static void on_click(const LeaderboardController* this, int x, int y) {
    if (is_on_element_click(this->layout.close_button, x, y))
        on_close_button_click(this);
}

static void on_update(const LeaderboardController* this, SDL_Renderer* renderer) {
    draw_leaderboard(renderer, *this->leader_board, this->layout);
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