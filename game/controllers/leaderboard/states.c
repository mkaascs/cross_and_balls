#include "../states.h"

#include "../controllers.h"
#include "../../../memstat/memstat.h"

static void handle_event(const GameState* state, SDL_Event* event) {
    LeaderboardScreenState* leaderboard_screen_state = (LeaderboardScreenState*)state;
    if (event->type != SDL_MOUSEBUTTONDOWN)
        return;

    leaderboard_screen_state->controller->on_click(leaderboard_screen_state->controller, event->button.x, event->button.y);
}

static void update(const GameState* state) {}

static void render(const GameState* state, SDL_Renderer* renderer) {
    LeaderboardScreenState* leaderboard_screen_state = (LeaderboardScreenState*)state;
    leaderboard_screen_state->controller->on_update(leaderboard_screen_state->controller, renderer);
}

static void destroy(const GameState* state) {
    LeaderboardScreenState* leaderboard_screen_state = (LeaderboardScreenState*)state;
    track_free((void**)&leaderboard_screen_state->controller);
    track_free((void**)&state);
}

GameState* init_leaderboard_state(WindowLayout layout, LeaderBoard* leaderboard, void (*change_state)(StateScreen)) {
    LeaderboardScreenState* state = track_malloc(sizeof(LeaderboardScreenState));
    state->controller = init_leaderboard_controller(layout, leaderboard, change_state);

    state->base.handle_event = handle_event;
    state->base.update = update;
    state->base.render = render;
    state->base.destroy = destroy;
    return (GameState*)state;
}