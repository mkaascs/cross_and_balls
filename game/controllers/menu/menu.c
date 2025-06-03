#include "../controllers.h"
#include "../states.h"
#include "../../../memstat/memstat.h"
#include "../../views/menu/views.h"

static bool is_on_element_click(ElementLayout element, int x, int y) {
    return x >= element.margin_x && x <= element.margin_x + element.width &&
        y >= element.margin_y && y <= element.margin_y + element.height;
}

static void on_click(const MenuController* this, int x, int y) {
    if (is_on_element_click(this->layout.menu.button, x, y)) {
        this->change_state(MODE_SCREEN);
        return;
    }

    ElementLayout leaderboard_button = {
        .margin_x = this->layout.menu.button.margin_x,
        .margin_y = this->layout.menu.button.margin_y + this->layout.menu.button.height + this->layout.menu.button_spacing,
        .width = this->layout.menu.button.width,
        .height = this->layout.menu.button.height
    };

    if (is_on_element_click(leaderboard_button, x, y))
        this->change_state(LEADERBOARD_SCREEN);
}

static void on_update(const MenuController* this, SDL_Renderer* renderer) {
    draw_menu(renderer, this->layout);
}

MenuController* init_menu_controller(WindowLayout layout, void (*change_state)(StateScreen)) {
    MenuController* controller = track_malloc(sizeof(MenuController));
    controller->change_state = change_state;
    controller->layout = layout;
    controller->on_click = on_click;
    controller->on_update = on_update;

    return controller;
}