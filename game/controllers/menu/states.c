#include "../states.h"

#include "../controllers.h"
#include "../../../memstat/memstat.h"

static void handle_event(const GameState* state, SDL_Event* event) {
    MenuScreenState* menu_state = (MenuScreenState*)state;
    if (event->type != SDL_MOUSEBUTTONDOWN)
        return;

    menu_state->controller->on_click(menu_state->controller, event->button.x, event->button.y);
}

static void update(const GameState* state) {}

static void render(const GameState* state, SDL_Renderer* renderer) {
    MenuScreenState* menu_state = (MenuScreenState*)state;
    menu_state->controller->on_update(menu_state->controller, renderer);
}

static void destroy(const GameState* state) {
    MenuScreenState* menu_state = (MenuScreenState*)state;
    track_free((void**)&menu_state->controller);
    track_free((void**)&state);
}

GameState* init_menu_state(WindowLayout layout, void (*change_state)(StateScreen)) {
    MenuScreenState* state = track_malloc(sizeof(MenuScreenState));
    state->controller = init_menu_controller(layout, change_state);

    state->base.handle_event = handle_event;
    state->base.update = update;
    state->base.render = render;
    state->base.destroy = destroy;
    return (GameState*)state;
}