#include "../states.h"

#include "../../../memstat/memstat.h"

static void handle_event(GameState* state, SDL_Event* event) {
    GameScreenState* game_state = (GameScreenState*)state;
    if (event->type != SDL_MOUSEBUTTONDOWN)
        return;

    if (game_state->controller->game->is_complete)
        game_state->controller->on_restart_button_click(game_state->controller, event->button.x, event->button.y);
    else
        game_state->controller->on_click(game_state->controller, event->button.x, event->button.y);
}

static void update(GameState* state) {}

static void render(GameState* state, SDL_Renderer* renderer) {
    GameScreenState* game_state = (GameScreenState*)state;
    game_state->controller->on_update(game_state->controller, renderer);
}

static void destroy(GameState* state) {
    GameScreenState* game_state = (GameScreenState*)state;
    track_free((void**)&game_state->controller);
    track_free((void**)&game_state);
}

GameState* init_game_state(SDL_Renderer* renderer, WindowLayout layout, Game* game) {
    GameScreenState* state = track_malloc(sizeof(GameScreenState));
    state->controller = init_board_controller(renderer, layout, game);

    state->base.handle_event = handle_event;
    state->base.update = update;
    state->base.render = render;
    state->base.destroy = destroy;
    return (GameState*)state;
}