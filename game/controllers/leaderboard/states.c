#include "../states.h"

#include "../controllers.h"
#include "../../../memstat/memstat.h"

static void handle_event(const GameState* state, SDL_Event* event) {
    LeaderBoardScreenState* leader_board_state = (LeaderBoardScreenState*)state;
    if (event->type != SDL_MOUSEBUTTONDOWN)
        return;

    leader_board_state->controller->on_click(leader_board_state->controller, event->button.x, event->button.y);
}

static void update(const GameState* state) {}

static void render(const GameState* state, SDL_Renderer* renderer) {
    LeaderBoardScreenState* leader_board_state = (LeaderBoardScreenState*)state;
    leader_board_state->controller->on_update(leader_board_state->controller, renderer);
}

static void destroy(const GameState* state) {
    LeaderBoardScreenState* leader_board_state = (LeaderBoardScreenState*)state;
    track_free((void**)&leader_board_state->controller);
    track_free((void**)&state);
}

GameState* init_leaderboard_state(WindowLayout layout, LeaderBoard* leader_board, void (*change_state)(StateScreen)) {
    LeaderBoardScreenState* state = track_malloc(sizeof(LeaderBoardScreenState));
    state->controller = init_leader_board_controller(layout, leader_board, change_state);

    state->base.handle_event = handle_event;
    state->base.update = update;
    state->base.render = render;
    state->base.destroy = destroy;
    return (GameState*)state;
}