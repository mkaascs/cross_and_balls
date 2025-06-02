#include "views.h"
#include "../primitives/primitives.h"
#define MAX_LEADERBOARD_ENTRIES 10

void draw_leaderboard(SDL_Renderer* renderer, LeaderBoard leaderboard, WindowLayout layout);

static void draw_gamer_nodes(SDL_Renderer* renderer, const GamerNode* node, int* count, WindowLayout layout) {
    if (node == NULL || *count > MAX_LEADERBOARD_ENTRIES)
        return;

    draw_gamer_nodes(renderer, node->left, count, layout);

    if (*count > MAX_LEADERBOARD_ENTRIES)
        return;

    char buffer[64];
    sprintf(buffer, "%d. @%s - %d", *count, node->gamer->name, node->gamer->score);
    SDL_Color color = { 0, 0, 0, 255 };

    draw_text_centred_x(
        renderer,
        buffer,
        layout.window_width,
        layout.leaderboard.margin_y + (*count - 1) * layout.leaderboard.row_height,
        layout.leaderboard.font_size,
        color
    );

    (*count)++;
    draw_gamer_nodes(renderer, node->right, count, layout);
}

void draw_leaderboard(SDL_Renderer* renderer, LeaderBoard leaderboard, WindowLayout layout) {
    draw_close_button(renderer, layout);

    int count = 1;
    draw_gamer_nodes(renderer, leaderboard.root, &count, layout);
}