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

static SDL_Texture* cross_texture = NULL;
static SDL_Texture* ball_texture = NULL;

bool load_sprites(SDL_Renderer* renderer) {
    SDL_Surface* cross_surface = SDL_LoadBMP("../../sprites/cross.bmp");
    if (cross_surface == NULL)
        return false;

    SDL_Surface* ball_surface = SDL_LoadBMP("../../sprites/ball.bmp");
    if (ball_surface == NULL) {
        SDL_FreeSurface(cross_surface);
        return false;
    }

    cross_texture = SDL_CreateTextureFromSurface(renderer, cross_surface);
    ball_texture = SDL_CreateTextureFromSurface(renderer, ball_surface);
    SDL_FreeSurface(cross_surface);
    SDL_FreeSurface(ball_surface);

    return cross_texture && ball_texture;
}

void free_sprites() {
    if (cross_texture) SDL_DestroyTexture(cross_texture);
    if (ball_texture) SDL_DestroyTexture(ball_texture);
    cross_texture = NULL;
    ball_texture = NULL;
}

void draw_cross(SDL_Renderer* renderer, SDL_Rect* rect) {
    if (cross_texture)
        SDL_RenderCopy(renderer, cross_texture, NULL, rect);
}

void draw_ball(SDL_Renderer* renderer, SDL_Rect* rect) {
    if (ball_texture)
        SDL_RenderCopy(renderer, ball_texture, NULL, rect);
}