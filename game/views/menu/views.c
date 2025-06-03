#include "views.h"

#include "../assets.h"
#include "../primitives/primitives.h"
#include "../primitives/input_box.h"

static InputBox input_box;

static void draw_logo(SDL_Renderer* renderer, WindowLayout layout) {
    SDL_Rect logo = {
        (int)layout.menu.logo.margin_x,
        (int)layout.menu.logo.margin_y,
        (int)layout.menu.logo.width,
        (int)layout.menu.logo.height
    };

    SDL_RenderCopy(renderer, get_sprite(SPRITE_LOGO), NULL, &logo);
}

void draw_menu(SDL_Renderer* renderer, WindowLayout layout) {
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

void init_menu_view(WindowLayout layout) {
    SDL_Rect input_box_rect = {
        (int)layout.menu.input_box.margin_x,
        (int)layout.menu.input_box.margin_y,
        (int)layout.menu.input_box.width,
        (int)layout.menu.input_box.height
    };

    TTF_Font* font = TTF_OpenFont(FONT_PATH, layout.menu.font_size);
    init_input_box(&input_box, input_box_rect, font);
}

void handle_input_box_event(SDL_Event* event, char* text) {
    handle_input_box(&input_box, event, text);
}