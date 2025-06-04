#include "views.h"

#include "../assets.h"
#include "../primitives/primitives.h"

static void draw_logo(SDL_Renderer* renderer, WindowLayout layout) {
    SDL_Rect logo = {
        (int)layout.menu.logo.margin_x,
        (int)layout.menu.logo.margin_y,
        (int)layout.menu.logo.width,
        (int)layout.menu.logo.height
    };

    SDL_RenderCopy(renderer, get_sprite(SPRITE_LOGO), NULL, &logo);
}

void draw_menu(SDL_Renderer* renderer, WindowLayout layout, InputBox input_box) {
    draw_logo(renderer, layout);
    render_input_box(&input_box, renderer);

    SDL_Rect button = {
        (int)layout.menu.button.margin_x,
        (int)layout.menu.button.margin_y,
        (int)layout.menu.button.width,
        (int)layout.menu.button.height
    };

    SDL_RenderCopy(renderer, get_sprite(SPRITE_PLAY_BUTTON), NULL, &button);

    button.y += (int)(layout.menu.button.height + layout.menu.button_spacing);

    SDL_RenderCopy(renderer, get_sprite(SPRITE_LEADERBOARD_BUTTON), NULL, &button);
}