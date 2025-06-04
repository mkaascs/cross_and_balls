#include "input_box.h"
#include "../primitives/primitives.h"

#include <string.h>

void init_input_box(InputBox* box, WindowLayout layout) {
    SDL_Rect input_box_rect = {
        (int)layout.menu.input_box.margin_x,
        (int)layout.menu.input_box.margin_y,
        (int)layout.menu.input_box.width,
        (int)layout.menu.input_box.height
    };

    TTF_Font* font = TTF_OpenFont(FONT_PATH, layout.menu.font_size);

    memset(box, 0, sizeof(InputBox));
    box->rect = input_box_rect;
    box->font = font;
    box->text_color = (SDL_Color){0, 0, 0, 255};
    box->bg_color = (SDL_Color){255, 255, 255, 255};
    box->border_color = (SDL_Color){100, 100, 100, 255};
    box->active = true;
    SDL_StartTextInput();
}

void render_input_box(InputBox* box, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer,
        box->bg_color.r, box->bg_color.g, box->bg_color.b, box->bg_color.a);
    SDL_RenderFillRect(renderer, &box->rect);

    SDL_SetRenderDrawColor(renderer,
        box->border_color.r, box->border_color.g, box->border_color.b, box->border_color.a);
    SDL_RenderDrawRect(renderer, &box->rect);

    if (box->length > 0) {
        SDL_Surface* surface = TTF_RenderText_Blended(box->font, box->text, box->text_color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_Rect text_rect = {
            box->rect.x + 8,
            box->rect.y + (box->rect.h - surface->h) / 2,
            surface->w,
            surface->h
        };

        SDL_RenderCopy(renderer, texture, NULL, &text_rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
}