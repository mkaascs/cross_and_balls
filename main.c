#include <SDL.h>

#include "game/game.h"
#include "game/config/config.h"
#include "game/views/board_view.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    WindowConfig* config = calloc(0, sizeof(WindowConfig));
    init_config(config);

    SDL_Window* window = SDL_CreateWindow("Tic-Tac-Toe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, config->window_width, config->window_height, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Game* game = calloc(0,sizeof(Game));
    run_game(game);

    bool running = true;
    SDL_Event event;

    draw_board(renderer, *game, *config);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    free(game);
    free(config);
}
