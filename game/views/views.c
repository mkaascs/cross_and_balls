#include "views.h"

void draw_grid(SDL_Renderer* renderer, WindowSize size) {
    const int left = (size.window_width - size.cell_size * 3) / 2;
    const int top = (size.window_height - size.cell_size * 3) / 2;

    for (int count = 0; count <= 3; count++) {
        thickLineRGBA(renderer, left + count * size.cell_size, top, left + count * size.cell_size, size.window_height - top, 3, 0, 0, 0, 255);
        thickLineRGBA(renderer, left, top + count * size.cell_size, size.window_width - left, top + count * size.cell_size, 3, 0, 0, 0, 255);
    }
}

void draw_board(SDL_Renderer* renderer, Game game, WindowSize size) {
    draw_grid(renderer, size);
    const int left = (size.window_width - size.cell_size * 3) / 2;
    const int top = (size.window_height - size.cell_size * 3) / 2;

    for (int index = 0; index < 9; index++) {
        SDL_Rect rect = {
            (index % 3) * size.cell_size + left + size.cell_padding,
            (index / 3) * size.cell_size + top + size.cell_padding,
            size.cell_size - 2 * size.cell_padding,
            size.cell_size - 2 * size.cell_padding
        };

        if (game.balls_moves & (1 << index))
            draw_ball(renderer, &rect);

        else if (game.crosses_moves & (1 << index))
            draw_cross(renderer, &rect);
    }
}

void draw_win_way(SDL_Renderer* renderer, uint16_t way, WindowSize size) {
    if (way == 0)
        return;

    const int left = (size.window_width - size.cell_size * 3) / 2;
    const int top = (size.window_height - size.cell_size * 3) / 2;

    int first_position = -1, last_position = -1;
    for (int index = 0; index < 9; index++) {
        if (!(way & (1 << index)))
            continue;

        first_position = first_position >= 0 ? first_position : index;
        last_position = index;
    }

    const int x1 = (first_position % 3) * size.cell_size + size.cell_size/2 + left;
    const int y1 = (first_position / 3) * size.cell_size + size.cell_size/2 + top;
    const int x2 = (last_position % 3) * size.cell_size + size.cell_size/2 + left;
    const int y2 = (last_position / 3) * size.cell_size + size.cell_size/2 + top;

    int thickness = 12;
    thickLineRGBA(renderer, x1, y1, x2, y2, thickness, 230, 15, 15, 255);
}

static SDL_Texture* cross_texture = NULL;
static SDL_Texture* ball_texture = NULL;

bool load_sprites(SDL_Renderer* renderer) {
    SDL_Surface* cross_surface = SDL_LoadBMP("sprites/cross.bmp");
    if (cross_surface == NULL)
        return false;

    SDL_Surface* ball_surface = SDL_LoadBMP("sprites/ball.bmp");
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

void draw_cross(SDL_Renderer* renderer, const SDL_Rect* rect) {
    if (cross_texture)
        SDL_RenderCopy(renderer, cross_texture, NULL, rect);
}

void draw_ball(SDL_Renderer* renderer, const SDL_Rect* rect) {
    if (ball_texture)
        SDL_RenderCopy(renderer, ball_texture, NULL, rect);
}