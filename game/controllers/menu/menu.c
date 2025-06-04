#include "../controllers.h"
#include "../states.h"
#include "../../../memstat/memstat.h"
#include "../../session/session.h"
#include "../../views/menu/views.h"

static bool is_on_element_click(ElementLayout element, int x, int y) {
    return x >= element.margin_x && x <= element.margin_x + element.width &&
        y >= element.margin_y && y <= element.margin_y + element.height;
}

static void change_state(const MenuController* this, StateScreen state) {
    set_session(this->input_box.text);
    this->change_state(state);
}

static void on_click(const MenuController* this, int x, int y) {
    if (is_on_element_click(this->layout.menu.button, x, y)) {
        change_state(this, MODE_SCREEN);
        return;
    }

    ElementLayout leaderboard_button = {
        .margin_x = this->layout.menu.button.margin_x,
        .margin_y = this->layout.menu.button.margin_y + this->layout.menu.button.height + this->layout.menu.button_spacing,
        .width = this->layout.menu.button.width,
        .height = this->layout.menu.button.height
    };

    if (is_on_element_click(leaderboard_button, x, y))
        change_state(this, LEADERBOARD_SCREEN);
}

static void on_text_input(MenuController* this, const SDL_Event* event) {
    if (!this->input_box.active) return;
    const int text_length = strlen(this->input_box.text);

    if (event->type == SDL_TEXTINPUT && text_length < INPUTBOX_MAX_LENGTH)
        strcat(this->input_box.text, event->text.text);

    if (event->type == SDL_KEYDOWN)
        if (event->key.keysym.sym == SDLK_BACKSPACE && text_length > 0)
            this->input_box.text[text_length - 1] = '\0';
}

static void on_update(const MenuController* this, SDL_Renderer* renderer) {
    draw_menu(renderer, this->layout, this->input_box);
}

MenuController* init_menu_controller(WindowLayout layout, void (*change_state)(StateScreen)) {
    MenuController* controller = track_malloc(sizeof(MenuController));
    controller->change_state = change_state;
    controller->layout = layout;
    controller->on_click = on_click;
    controller->on_update = on_update;
    controller->on_text_input = on_text_input;

    init_input_box(&controller->input_box, layout);
    GameSession* game_session = get_current_session();
    if (strlen(game_session->gamer_name) > 0) {
        strncpy(controller->input_box.text, game_session->gamer_name, NAME_LENGTH);
        controller->input_box.text[NAME_LENGTH - 1] = '\0';
    }

    return controller;
}