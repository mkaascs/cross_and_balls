#include <SDL.h>

#include "game/domain/game.h"
#include "game/controllers/controllers.h"
#include "game/views/layout/layout.h"
#include "game/views/views.h"

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

    if (!load_sprites(renderer)) {
        fprintf(stderr, "Failed to load sprites\n");
        free(layout);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Game* game = init_game();
    BoardController* board_controller = init_board_controller(renderer, *layout, game);
    MainController* main_controller = init_main_controller(renderer, *layout, game);

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                board_controller->on_click(board_controller, event.button.x, event.button.y);
                main_controller->on_restart_button_click(main_controller, event.button.x, event.button.y);
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        board_controller->on_update(board_controller);

        SDL_RenderPresent(renderer);

        SDL_Delay(16); // ~60 fps
    }

    free_sprites();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    free_query(game->balls);
    free_query(game->crosses);
    free(game);
    free(layout);
    free(board_controller);
}
