#include <SDL.h>
#include <SDL_ttf.h>

#include "game/controllers/controllers.h"
#include "game/controllers/states.h"
#include "game/domain/entities/leaderboard.h"
#include "game/views/layout/layout.h"
#include "game/views/assets.h"
#include "memstat/memstat.h"

#define MEMSTAT_FILENAME "memstat.txt"
#define LEADERBOARD_FILENAME "leaderboard.txt"

static GameState* current_state = NULL;

static WindowLayout* global_layout = NULL;
static Game* global_game = NULL;
static LeaderBoard* global_leader_board = NULL;

static void change_screen(StateScreen screen) {
    if (current_state)
        current_state->destroy(current_state);

    switch (screen) {
        case MENU_SCREEN:
            current_state = init_menu_state(*global_layout, change_screen);
        break;
        case GAME_SCREEN:
            current_state = init_game_state(*global_layout, global_game, change_screen);
        break;
        case LEADERBOARD_SCREEN:
            current_state = init_leaderboard_state(*global_layout, global_leader_board, change_screen);
        break;
    }
}

int main() {
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    global_layout = init_window_layout();

    SDL_Window* window = SDL_CreateWindow("Tic-Tac-Toe",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        global_layout->window_width,
        global_layout->window_height,
        0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!load_assets(renderer)) {
        fprintf(stderr, "Failed to load sprites\n");
        free(global_layout);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    global_game = init_game();

    FILE* leader_board_file = fopen(LEADERBOARD_FILENAME, "r");
    global_leader_board = init_leader_board_from_file(leader_board_file);

    fclose(leader_board_file);
    current_state = init_menu_state(*global_layout, change_screen);

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;

            if (event.type == SDL_MOUSEBUTTONDOWN)
                current_state->handle_event(current_state, &event);
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        current_state->render(current_state, renderer);

        SDL_RenderPresent(renderer);

        SDL_Delay(16); // ~60 fps
    }

    free_assets();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    current_state->destroy(current_state);
    track_free((void**)&global_layout);
    free_leader_board(global_leader_board);
    free_game(global_game);

    Memstat memstat;
    get_memstat(&memstat);
    FILE* memstat_file = fopen("memstat.txt", "w");
    if (memstat_file == NULL)
        return 1;

    fprintf(memstat_file, "malloc:%lu\ncalloc:%lu\nrealloc:%lu\nfree:%lu",
        memstat.malloc_count, memstat.calloc_count, memstat.realloc_count, memstat.free_count);

    fclose(memstat_file);
    return 0;
}
