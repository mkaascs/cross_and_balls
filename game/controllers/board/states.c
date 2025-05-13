#include "../states.h"

#include "../controllers.h"
#include "../../../memstat/memstat.h"

static void handle_event(const GameState* state, SDL_Event* event) {
    GameScreenState* game_state = (GameScreenState*)state;
    if (event->type != SDL_MOUSEBUTTONDOWN)
        return;

    game_state->controller->on_click(game_state->controller, event->button.x, event->button.y);
}

static void update(const GameState* state) {}

static void render(const GameState* state, SDL_Renderer* renderer) {
    GameScreenState* game_state = (GameScreenState*)state;
    game_state->controller->on_update(game_state->controller, renderer);
}

static void destroy(const GameState* state) {
    GameScreenState* game_state = (GameScreenState*)state;
    track_free((void**)&game_state->controller);
    track_free((void**)&state);
}

GameState* init_game_state(WindowLayout layout, Game* game, void (*change_state)(StateScreen)) {
    GameScreenState* state = track_malloc(sizeof(GameScreenState));
    state->controller = init_board_controller(layout, game, change_state);

    state->base.handle_event = handle_event;
    state->base.update = update;
    state->base.render = render;
    state->base.destroy = destroy;
    return (GameState*)state;
}