#include "../states.h"

#include "../controllers.h"
#include "../../../memstat/memstat.h"

static void handle_event(const GameState* state, SDL_Event* event) {
    ModeScreenState* mode_state = (ModeScreenState*)state;
    if (event->type != SDL_MOUSEBUTTONDOWN)
        return;

    mode_state->controller->on_click(mode_state->controller, event->button.x, event->button.y);
}

static void update(const GameState* state) {}

static void render(const GameState* state, SDL_Renderer* renderer) {
    ModeScreenState* mode_state = (ModeScreenState*)state;
    mode_state->controller->on_update(mode_state->controller, renderer);
}

static void destroy(const GameState* state) {
    ModeScreenState* mode_state = (ModeScreenState*)state;
    track_free((void**)&mode_state->controller);
    track_free((void**)&state);
}

GameState* init_mode_state(WindowLayout layout, void (*change_state)(StateScreen)) {
    ModeScreenState* state = track_malloc(sizeof(ModeScreenState));
    state->controller = init_mode_controller(layout, change_state);

    state->base.handle_event = handle_event;
    state->base.update = update;
    state->base.render = render;
    state->base.destroy = destroy;
    return (GameState*)state;
}