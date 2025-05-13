#include "primitives.h"
#include "../assets.h"

void draw_close_button(SDL_Renderer* renderer, WindowLayout layout) {
    SDL_Rect button = {
        layout.close_button_x,
        layout.close_button_y,
        layout.close_button_width,
        layout.close_button_height
    };

    if (close_button_texture)
        SDL_RenderCopy(renderer, close_button_texture, NULL, &button);
}