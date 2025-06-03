#include "views.h"
#include "../primitives/primitives.h"
#include "../assets.h"


void draw_mode_choice(SDL_Renderer* renderer, WindowLayout layout) {
    draw_close_button(renderer, layout);

    for (int index = 0; index < MODE_BUTTONS_COUNT; index++) {
        SDL_Rect button = {
            (int)layout.mode.button.margin_x,
            (int)layout.mode.button.margin_y + index * (layout.mode.button.height + layout.mode.button_spacing),
            (int)layout.mode.button.width,
            (int)layout.mode.button.height
        };

        SDL_RenderCopy(renderer, get_sprite(SPRITE_DIFFICULTY_EASY_BUTTON + index), NULL, &button);
    }
}