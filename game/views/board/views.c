#include "views.h"
#include "../primitives/primitives.h"
#include "../assets.h"

#define RESTART_BUTTON_WIDTH 116
#define RESTART_BUTTON_HEIGHT 42

static void draw_cross(SDL_Renderer* renderer, const SDL_Rect* rect) {
    SDL_RenderCopy(renderer, get_sprite(SPRITE_CROSS), NULL, rect);
}

static void draw_ball(SDL_Renderer* renderer, const SDL_Rect* rect) {
    SDL_RenderCopy(renderer, get_sprite(SPRITE_BALL), NULL, rect);
}

static void draw_grid(SDL_Renderer* renderer, WindowLayout layout) {
    for (int count = 0; count <= 3; count++) {
        thickLineRGBA(renderer,
            layout.board.cell_left + count * layout.board.cell_size,
            layout.board.cell_top,
            layout.board.cell_left + count * layout.board.cell_size,
            layout.window_height - layout.board.cell_top,
            3, 0, 0, 0, 255);

        thickLineRGBA(renderer,
            layout.board.cell_left,
            layout.board.cell_top + count * layout.board.cell_size,
            layout.window_width - layout.board.cell_left,
            layout.board.cell_top + count * layout.board.cell_size,
            3, 0, 0, 0, 255);
    }
}

static void draw_default_text(SDL_Renderer* renderer, int x, int y, const char* text) {
    stringRGBA(renderer, x, y, text, 30, 30, 30, 255);
}

static void draw_score(SDL_Renderer* renderer, GameScore score, WindowLayout layout) {
    char buffer[8];
    sprintf(buffer, "%d : %d", score.cross_score, score.ball_score);

    SDL_Color color = {0,0,0,255};
    draw_text_centred_x(renderer, buffer, layout.window_width, layout.padding_top, 32, color);
}

static void draw_moves_query(SDL_Renderer* renderer, MoveQuery* query, WindowLayout layout) {
    int count = 1;
    MoveElement* current = query->tail;
    while (current != NULL) {
        int x = (current->position % 3) * layout.board.cell_size + layout.board.cell_left;
        int y = (current->position / 3) * layout.board.cell_size + layout.board.cell_top;

        char text[2];
        sprintf(text, "%d", 3 + (count++ - 1) - (query->length - 1));
        draw_default_text(renderer,
            x + layout.board.cell_size - layout.board.cell_padding,
            y + layout.board.cell_size - layout.board.cell_padding,
            text);

        current = current->next;
    }
}

void draw_restart_button(SDL_Renderer* renderer, WindowLayout layout) {
    SDL_Rect button = {
        layout.board.restart_button_x,
        layout.board.restart_button_y,
        layout.board.restart_button_width,
        layout.board.restart_button_height
    };

    SDL_RenderCopy(renderer, get_sprite(SPRITE_RESTART_BUTTON), NULL, &button);
}

void draw_board(SDL_Renderer* renderer, Game game, WindowLayout layout) {
    draw_grid(renderer, layout);
    draw_close_button(renderer, layout);
    draw_score(renderer, game.score, layout);
    for (int index = 0; index < 9; index++) {
        SDL_Rect rect = {
            (index % 3) * layout.board.cell_size + layout.board.cell_left + layout.board.cell_padding,
            (index / 3) * layout.board.cell_size + layout.board.cell_top + layout.board.cell_padding,
            layout.board.cell_size - 2 * layout.board.cell_padding,
            layout.board.cell_size - 2 * layout.board.cell_padding
        };

        if (game.balls_moves & (1 << index))
            draw_ball(renderer, &rect);

        else if (game.crosses_moves & (1 << index))
            draw_cross(renderer, &rect);
    }
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

    const int x1 = (first_position % 3) * layout.board.cell_size + layout.board.cell_size/2 + layout.board.cell_left;
    const int y1 = (first_position / 3) * layout.board.cell_size + layout.board.cell_size/2 + layout.board.cell_top;
    const int x2 = (last_position % 3) * layout.board.cell_size + layout.board.cell_size/2 + layout.board.cell_left;
    const int y2 = (last_position / 3) * layout.board.cell_size + layout.board.cell_size/2 + layout.board.cell_top;

    int thickness = 12;
    thickLineRGBA(renderer, x1, y1, x2, y2, thickness, 230, 15, 15, 255);
}