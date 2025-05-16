#include "assets.h"

typedef struct {
    const char* path;
    SDL_Texture* texture;
} SpriteResource;

static SpriteResource sprite_table[SPRITE_COUNT] = {
    [SPRITE_CROSS]              = { "assets/sprites/cross.bmp", NULL },
    [SPRITE_BALL]               = { "assets/sprites/ball.bmp", NULL },
    [SPRITE_RESTART_BUTTON]     = { "assets/sprites/button_restart.bmp", NULL },
    [SPRITE_CLOSE_BUTTON]       = { "assets/sprites/close_button.bmp", NULL },
    [SPRITE_LOGO]               = { "assets/sprites/logo.bmp", NULL },
    [SPRITE_PLAY_BUTTON]        = { "assets/sprites/button_play.bmp", NULL},
    [SPRITE_LEADERBOARD_BUTTON] = { "assets/sprites/button_leaderboard.bmp", NULL}
};

bool load_assets(SDL_Renderer* renderer) {
    for (int i = 0; i < SPRITE_COUNT; i++) {
        SDL_Surface* surface = SDL_LoadBMP(sprite_table[i].path);
        if (surface == NULL) {
            SDL_Log("Failed to load: %s", sprite_table[i].path);
            return false;
        }

        sprite_table[i].texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        if (sprite_table[i].texture == NULL) {
            SDL_Log("Failed to create texture from: %s", sprite_table[i].path);
            return false;
        }
    }

    return true;
}

void free_assets() {
    for (int i = 0; i < SPRITE_COUNT; i++) {
        if (sprite_table[i].texture) {
            SDL_DestroyTexture(sprite_table[i].texture);
            sprite_table[i].texture = NULL;
        }
    }
}

SDL_Texture* get_sprite(SpriteID id) {
    if (id >= SPRITE_COUNT)
        return NULL;

    return sprite_table[id].texture;
}