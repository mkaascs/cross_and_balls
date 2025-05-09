#include <SDL.h>

#include "game/domain/game.h"
#include "game/controllers/controllers.h"
#include "game/controllers/states.h"
#include "game/views/layout/layout.h"
#include "game/views/assets.h"
#include "memstat/memstat.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    WindowLayout* layout = init_window_layout();

    SDL_Window* window = SDL_CreateWindow("Tic-Tac-Toe",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        layout->window_width,
        layout->window_height,
        0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!load_assets(renderer)) {
        fprintf(stderr, "Failed to load sprites\n");
        free(layout);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Game* game = init_game();

    GameState* current_state = init_game_state(renderer, *layout, game);

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

    free_query(game->balls);
    free_query(game->crosses);
    track_free((void**)&game);
    track_free((void**)&layout);
    current_state->destroy(current_state);

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
