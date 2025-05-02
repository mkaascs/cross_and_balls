#include "board_view.h"
#include "symbols_view.h"

void draw_grid(SDL_Renderer* renderer, WindowConfig config) {
    int left = (config.window_width - config.cell_size * 3) / 2;
    int top = (config.window_height - config.cell_size * 3) / 2;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int count = 0; count <= 3; count++) {
        SDL_RenderDrawLine(renderer, left + count * config.cell_size, top, left + count * config.cell_size, config.window_height - top);
        SDL_RenderDrawLine(renderer, left, top + count * config.cell_size, config.window_width - left, top + count * config.cell_size);
    }
}

void draw_board(SDL_Renderer* renderer, Game game, WindowConfig config) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    draw_grid(renderer, config);

    SDL_RenderPresent(renderer);
}