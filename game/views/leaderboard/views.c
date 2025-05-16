#include "views.h"
#include "../primitives/primitives.h"

void draw_leaderboard(SDL_Renderer* renderer, LeaderBoard leaderboard, WindowLayout layout) {
    draw_close_button(renderer, layout);

    int count = 1;
    Gamer* current = leaderboard.head;
    SDL_Color color = { 0, 0, 0, 255 };

    while (current) {
        char buffer[64];
        sprintf(buffer, "%d.   @%s - %d", count, current->name, current->score);
        draw_text_centred_x(renderer,
            buffer,
            layout.window_width,
            layout.leaderboard.top + (count-1)*layout.leaderboard.player_label_height,
            layout.leaderboard.font_size,
            color);

        count++;
        current = current->next;
    }
}