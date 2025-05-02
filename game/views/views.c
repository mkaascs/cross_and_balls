#include "views.h"

void draw_grid(SDL_Renderer* renderer, WindowSize size) {
    int left = (size.window_width - size.cell_size * 3) / 2;
    int top = (size.window_height - size.cell_size * 3) / 2;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int count = 0; count <= 3; count++) {
        SDL_RenderDrawLine(renderer, left + count * size.cell_size, top, left + count * size.cell_size, size.window_height - top);
        SDL_RenderDrawLine(renderer, left, top + count * size.cell_size, size.window_width - left, top + count * size.cell_size);
    }
}

void draw_board(SDL_Renderer* renderer, Game game, WindowSize size) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    draw_grid(renderer, size);

    SDL_RenderPresent(renderer);
}

void draw_cross(SDL_Renderer*, SDL_Rect*) {

}

void draw_ball(SDL_Renderer*, SDL_Rect*) {

}