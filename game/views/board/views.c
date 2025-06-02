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
    const float cell_size = layout.board.cell.width;
    const float cell_left = layout.board.cell.margin_x;
    const float cell_top = layout.board.cell.margin_y;

    for (int count = 0; count <= 3; count++) {
        // Вертикальные линии
        thickLineRGBA(renderer,
            (int)(cell_left + count * cell_size),
            (int)cell_top,
            (int)(cell_left + count * cell_size),
            (int)(cell_top + 3 * cell_size),
            3, 0, 0, 0, 255);

        // Горизонтальные линии
        thickLineRGBA(renderer,
            (int)cell_left,
            (int)(cell_top + count * cell_size),
            (int)(cell_left + 3 * cell_size),
            (int)(cell_top + count * cell_size),
            3, 0, 0, 0, 255);
    }
}

static void draw_score(SDL_Renderer* renderer, GameScore score, WindowLayout layout) {
    char buffer[8];
    sprintf(buffer, "%d : %d", score.cross_score, score.ball_score);

    SDL_Color color = {0,0,0,255};
    draw_text_centred_x(renderer, buffer, layout.window_width,
        (int)layout.close_button.margin_y, 32, color);
}

static void draw_default_text(SDL_Renderer* renderer, int x, int y, const char* text) {
    stringRGBA(renderer, x, y, text, 30, 30, 30, 255);
}

static void draw_moves_query(SDL_Renderer* renderer, MoveQuery* query, WindowLayout layout) {
    int count = 1;
    MoveElement* current = query->tail;
    const float cell_size = layout.board.cell.width;
    const float cell_left = layout.board.cell.margin_x;
    const float cell_top = layout.board.cell.margin_y;
    const float padding = layout.board.cell.padding;

    while (current != NULL) {
        int x = (int)((current->position % 3) * cell_size + cell_left);
        int y = (int)((current->position / 3) * cell_size + cell_top);

        char text[2];
        sprintf(text, "%d", 3 + (count++ - 1) - (query->length - 1));
        draw_default_text(renderer,
            (int)(x + cell_size - padding),
            (int)(y + cell_size - padding),
            text);

        current = current->next;
    }
}

static void draw_restart_button(SDL_Renderer* renderer, WindowLayout layout) {
    SDL_Rect button = {
        (int)layout.board.restart_button.margin_x,
        (int)layout.board.restart_button.margin_y,
        (int)layout.board.restart_button.width,
        (int)layout.board.restart_button.height
    };

    SDL_RenderCopy(renderer, get_sprite(SPRITE_RESTART_BUTTON), NULL, &button);
}

static void draw_win_way(SDL_Renderer* renderer, uint16_t way, WindowLayout layout) {
    if (way == 0)
        return;

    const float cell_size = layout.board.cell.width;
    const float cell_left = layout.board.cell.margin_x;
    const float cell_top = layout.board.cell.margin_y;

    int first_position = -1, last_position = -1;
    for (int index = 0; index < 9; index++) {
        if (!(way & (1 << index)))
            continue;

        first_position = first_position >= 0 ? first_position : index;
        last_position = index;
    }

    const int x1 = (int)((first_position % 3) * cell_size + cell_size/2 + cell_left);
    const int y1 = (int)((first_position / 3) * cell_size + cell_size/2 + cell_top);
    const int x2 = (int)((last_position % 3) * cell_size + cell_size/2 + cell_left);
    const int y2 = (int)((last_position / 3) * cell_size + cell_size/2 + cell_top);

    int thickness = 12;
    thickLineRGBA(renderer, x1, y1, x2, y2, thickness, 230, 15, 15, 255);
}

void draw_board(SDL_Renderer* renderer, Game game, WindowLayout layout) {
    draw_grid(renderer, layout);
    draw_close_button(renderer, layout);
    draw_score(renderer, game.score, layout);

    const float cell_size = layout.board.cell.width;
    const float cell_left = layout.board.cell.margin_x;
    const float cell_top = layout.board.cell.margin_y;
    const float padding = layout.board.cell.padding;

    for (int index = 0; index < 9; index++) {
        SDL_Rect rect = {
            (int)((index % 3) * cell_size + cell_left + padding),
            (int)((index / 3) * cell_size + cell_top + padding),
            (int)(cell_size - 2 * padding),
            (int)(cell_size - 2 * padding)
        };

        if (game.balls_moves & (1 << index))
            draw_ball(renderer, &rect);

        else if (game.crosses_moves & (1 << index))
            draw_cross(renderer, &rect);
    }

    if (game.is_complete) {
        draw_restart_button(renderer, layout);
        draw_win_way(renderer, game.get_win_way(&game), layout);
    }
}