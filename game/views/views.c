#include "views.h"

#define RESTART_BUTTON_WIDTH 116
#define RESTART_BUTTON_HEIGHT 42

static SDL_Texture* cross_texture = NULL;
static SDL_Texture* ball_texture = NULL;
static SDL_Texture* restart_button_texture = NULL;

void draw_grid(SDL_Renderer* renderer, WindowLayout layout) {
    for (int count = 0; count <= 3; count++) {
        thickLineRGBA(renderer,
            layout.cell_left + count * layout.cell_size,
            layout.cell_top,
            layout.cell_left + count * layout.cell_size,
            layout.window_height - layout.cell_top,
            3, 0, 0, 0, 255);

        thickLineRGBA(renderer,
            layout.cell_left,
            layout.cell_top + count * layout.cell_size,
            layout.window_width - layout.cell_left,
            layout.cell_top + count * layout.cell_size,
            3, 0, 0, 0, 255);
    }
}

void draw_text(SDL_Renderer* renderer, int x, int y, const char* text) {
    stringRGBA(renderer, x, y, text, 30, 30, 30, 255);
}

void draw_moves_query(SDL_Renderer* renderer, MoveQuery* query, WindowLayout layout) {
    int count = 1;
    MoveElement* current = query->tail;
    while (current != NULL) {
        int x = (current->position % 3) * layout.cell_size + layout.cell_left;
        int y = (current->position / 3) * layout.cell_size + layout.cell_top;

        char text[2];
        sprintf(text, "%d", count++);
        draw_text(renderer,
            x + layout.cell_size - layout.cell_padding,
            y + layout.cell_size - layout.cell_padding,
            text);

        current = current->next;
    }
}

void draw_board(SDL_Renderer* renderer, Game game, WindowLayout layout) {
    draw_grid(renderer, layout);
    for (int index = 0; index < 9; index++) {
        SDL_Rect rect = {
            (index % 3) * layout.cell_size + layout.cell_left + layout.cell_padding,
            (index / 3) * layout.cell_size + layout.cell_top + layout.cell_padding,
            layout.cell_size - 2 * layout.cell_padding,
            layout.cell_size - 2 * layout.cell_padding
        };

        if (game.balls_moves & (1 << index))
            draw_ball(renderer, &rect);

        else if (game.crosses_moves & (1 << index))
            draw_cross(renderer, &rect);
    }

    draw_moves_query(renderer, game.crosses, layout);
    draw_moves_query(renderer, game.balls, layout);
}

void draw_win_way(SDL_Renderer* renderer, uint16_t way, WindowLayout layout) {
    if (way == 0)
        return;

    int first_position = -1, last_position = -1;
    for (int index = 0; index < 9; index++) {
        if (!(way & (1 << index)))
            continue;

        first_position = first_position >= 0 ? first_position : index;
        last_position = index;
    }

    const int x1 = (first_position % 3) * layout.cell_size + layout.cell_size/2 + layout.cell_left;
    const int y1 = (first_position / 3) * layout.cell_size + layout.cell_size/2 + layout.cell_top;
    const int x2 = (last_position % 3) * layout.cell_size + layout.cell_size/2 + layout.cell_left;
    const int y2 = (last_position / 3) * layout.cell_size + layout.cell_size/2 + layout.cell_top;

    int thickness = 12;
    thickLineRGBA(renderer, x1, y1, x2, y2, thickness, 230, 15, 15, 255);
}

bool load_sprites(SDL_Renderer* renderer) {
    SDL_Surface* cross_surface = SDL_LoadBMP("sprites/cross.bmp");
    if (cross_surface == NULL)
        return false;

    SDL_Surface* ball_surface = SDL_LoadBMP("sprites/ball.bmp");
    if (ball_surface == NULL) {
        SDL_FreeSurface(cross_surface);
        return false;
    }

    SDL_Surface* restart_button_surface = SDL_LoadBMP("sprites/button_restart.bmp");
    if (restart_button_surface == NULL) {
        SDL_FreeSurface(cross_surface);
        SDL_FreeSurface(ball_surface);
        return false;
    }

    cross_texture = SDL_CreateTextureFromSurface(renderer, cross_surface);
    ball_texture = SDL_CreateTextureFromSurface(renderer, ball_surface);
    restart_button_texture = SDL_CreateTextureFromSurface(renderer, restart_button_surface);
    SDL_FreeSurface(cross_surface);
    SDL_FreeSurface(ball_surface);
    SDL_FreeSurface(restart_button_surface);

    return cross_texture && ball_texture && restart_button_texture;
}

void free_sprites() {
    if (cross_texture) SDL_DestroyTexture(cross_texture);
    if (ball_texture) SDL_DestroyTexture(ball_texture);
    if (restart_button_texture) SDL_DestroyTexture(restart_button_texture);
    cross_texture = NULL;
    ball_texture = NULL;
    restart_button_texture = NULL;
}

void draw_cross(SDL_Renderer* renderer, const SDL_Rect* rect) {
    if (cross_texture)
        SDL_RenderCopy(renderer, cross_texture, NULL, rect);
}

void draw_ball(SDL_Renderer* renderer, const SDL_Rect* rect) {
    if (ball_texture)
        SDL_RenderCopy(renderer, ball_texture, NULL, rect);
}

void draw_restart_button(SDL_Renderer* renderer, WindowLayout layout) {
    SDL_Rect button = {
        layout.restart_button_x,
        layout.restart_button_y,
        layout.restart_button_width,
        layout.restart_button_height
    };

    if (restart_button_texture)
        SDL_RenderCopy(renderer, restart_button_texture, NULL, &button);
}