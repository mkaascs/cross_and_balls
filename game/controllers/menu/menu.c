#include "../controllers.h"
#include "../states.h"
#include "../../../memstat/memstat.h"
#include "../../views/menu/views.h"

static void on_update(const MenuController* this, SDL_Renderer* renderer) {
    draw_menu(renderer, this->layout);
}

static void on_click(const MenuController* this, int x, int y) {
    if (y <= this->layout.window_height / 2)
        this->change_state(GAME_SCREEN);

    else this->change_state(LEADERBOARD_SCREEN);
}

MenuController* init_menu_controller(WindowLayout layout, void (*change_state)(StateScreen)) {
    MenuController* controller = track_malloc(sizeof(MenuController));
    controller->change_state = change_state;
    controller->layout = layout;
    controller->on_click = on_click;
    controller->on_update = on_update;

    return controller;
}