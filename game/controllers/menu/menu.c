#include "../controllers.h"
#include "../states.h"
#include "../../../memstat/memstat.h"
#include "../../views/menu/views.h"

static void on_update(const MenuController* this, SDL_Renderer* renderer) {
    draw_menu(renderer, this->layout);
}

static void on_click(const MenuController* this, int x, int y) {
    if (x >= this->layout.menu.button_x && x <= this->layout.menu.button_x + this->layout.menu.button_width &&
        y >= this->layout.menu.first_button_y && y <= this->layout.menu.first_button_y + this->layout.menu.button_height) {
        this->change_state(GAME_SCREEN);
        return;
        }

    if (x >= this->layout.menu.button_x && x <= this->layout.menu.button_x + this->layout.menu.button_width &&
        y >= this->layout.menu.first_button_y + this->layout.close_button_height + this->layout.padding_top && y <= this->layout.menu.first_button_y + 2*this->layout.menu.button_height + this->layout.padding_top) {
        this->change_state(LEADERBOARD_SCREEN);
        }
}

MenuController* init_menu_controller(WindowLayout layout, void (*change_state)(StateScreen)) {
    MenuController* controller = track_malloc(sizeof(MenuController));
    controller->change_state = change_state;
    controller->layout = layout;
    controller->on_click = on_click;
    controller->on_update = on_update;

    return controller;
}