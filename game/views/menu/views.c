#include "views.h"

#include "../assets.h"

void draw_logo(SDL_Renderer* renderer, WindowLayout layout) {
    SDL_Rect logo = {
        layout.menu.logo_x,
        layout.menu.logo_y,
        layout.menu.logo_width,
        layout.menu.logo_height
    };

    if (logo_texture)
        SDL_RenderCopy(renderer, logo_texture, NULL, &logo);
}

void draw_menu(SDL_Renderer* renderer, WindowLayout layout) {
    draw_logo(renderer, layout);
}