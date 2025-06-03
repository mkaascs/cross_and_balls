#include "../controllers.h"
#include "../states.h"
#include "../../../memstat/memstat.h"
#include "../../ai/ai.h"
#include "../../views/mode/views.h"

static bool is_on_element_click(ElementLayout element, int x, int y) {
    return x >= element.margin_x && x <= element.margin_x + element.width &&
        y >= element.margin_y && y <= element.margin_y + element.height;
}

static void on_close_button_click(const ModeController* this) {
    this->change_state(MENU_SCREEN);
}

static void on_click(const ModeController* this, int x, int y) {
    if (is_on_element_click(this->layout.close_button, x, y))
        on_close_button_click(this);

    if (x < this->layout.mode.button.margin_x || y < this->layout.mode.button.margin_y)
        return;

    ElementLayout mode_button = {
        .margin_x = this->layout.mode.button.margin_x,
        .margin_y = this->layout.mode.button.margin_y,
        .width = this->layout.mode.button.width,
        .height = this->layout.mode.button.height
    };

    for (int index = 0; index < MODE_BUTTONS_COUNT; index++) {
        if (is_on_element_click(mode_button, x, y)) {
            if (index == 3) {
                set_max_moves_count(3);
                set_difficulty(BOT_DIFFICULTY_MEDIUM);
            }

            else {
                set_max_moves_count(9);
                set_difficulty(BOT_DIFFICULTY_EASY + index);
            }

            this->change_state(GAME_SCREEN);
            return;
        }

        mode_button.margin_y += this->layout.menu.button.height + this->layout.menu.button_spacing;
    }
}

static void on_update(const ModeController* this, SDL_Renderer* renderer) {
    draw_mode_choice(renderer, this->layout);
}

ModeController* init_mode_controller(WindowLayout layout, void (*change_state)(StateScreen)) {
    ModeController* controller = track_malloc(sizeof(ModeController));
    controller->change_state = change_state;
    controller->layout = layout;
    controller->on_click = on_click;
    controller->on_update = on_update;

    return controller;
}