#include "views.h"

#include "../assets.h"

void draw_logo(SDL_Renderer* renderer, WindowLayout layout) {
    SDL_Rect logo = {
        layout.menu.logo_x,
        layout.menu.logo_y,
        layout.menu.logo_width,
        layout.menu.logo_height
    };

    SDL_RenderCopy(renderer, get_sprite(SPRITE_LOGO), NULL, &logo);
}

void draw_menu(SDL_Renderer* renderer, WindowLayout layout) {
    draw_logo(renderer, layout);

    SDL_Rect button = {
        layout.menu.button_x,
        layout.menu.first_button_y,
        layout.menu.button_width,
        layout.menu.button_height
    };

    SDL_RenderCopy(renderer, get_sprite(SPRITE_PLAY_BUTTON), NULL, &button);

    button.y += layout.menu.button_height + layout.padding_top;

    SDL_RenderCopy(renderer, get_sprite(SPRITE_LEADERBOARD_BUTTON), NULL, &button);
}