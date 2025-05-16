#include "primitives.h"
#include "../assets.h"

#define FONT_PATH ""

void draw_close_button(SDL_Renderer* renderer, WindowLayout layout) {
    SDL_Rect button = {
        layout.close_button_x,
        layout.close_button_y,
        layout.close_button_width,
        layout.close_button_height
    };

    SDL_RenderCopy(renderer, get_sprite(SPRITE_CLOSE_BUTTON), NULL, &button);
}

void draw_text(SDL_Renderer* renderer, const char* text, int x, int y, int font_size, SDL_Color color) {
    TTF_Font* font = TTF_OpenFont("assets/fonts/cal-sans.ttf", font_size);
    if (font == NULL) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return;
    }

    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        SDL_Log("Failed to create texture: %s", SDL_GetError());
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
        return;
    }

    SDL_Rect dst = { x, y, surface->w, surface->h };

    SDL_RenderCopy(renderer, texture, NULL, &dst);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

void draw_text_centred_x(SDL_Renderer* renderer, const char* text, int rect_width, int y, int font_size, SDL_Color color) {
    TTF_Font* font = TTF_OpenFont("assets/fonts/cal-sans.ttf", font_size);
    if (font == NULL) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return;
    }

    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        SDL_Log("Failed to create texture: %s", SDL_GetError());
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
        return;
    }

    SDL_Rect dst = { (rect_width - surface->w) / 2, y, surface->w, surface->h };

    SDL_RenderCopy(renderer, texture, NULL, &dst);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}