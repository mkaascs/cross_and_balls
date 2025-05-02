#include <SDL.h>

#include "game/domain/game.h"
#include "game/controllers/controllers.h"
#include "game/views/window/size.h"
#include "game/views/views.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    WindowSize* size = init_window_size();

    SDL_Window* window = SDL_CreateWindow("Tic-Tac-Toe",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        size->window_width,
        size->window_height,
        0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Game* game = init_game();
    BoardController* board_controller = init_controller(*size, game);

    bool running = true;
    SDL_Event event;

    draw_board(renderer, *game, *size);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;

            if (event.type == SDL_MOUSEBUTTONDOWN)
                board_controller->on_click(board_controller, event.button.x, event.button.y);
        }

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    free(game);
    free(size);
    free(board_controller);
}
