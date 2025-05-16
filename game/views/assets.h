#ifndef ASSETS_H
#define ASSETS_H
#include <SDL.h>
#include <stdbool.h>

typedef enum {
    SPRITE_CROSS,
    SPRITE_BALL,
    SPRITE_RESTART_BUTTON,
    SPRITE_CLOSE_BUTTON,
    SPRITE_LOGO,
    SPRITE_PLAY_BUTTON,
    SPRITE_LEADERBOARD_BUTTON,
    SPRITE_COUNT
} SpriteID;

void free_assets();
bool load_assets(SDL_Renderer*);
SDL_Texture* get_sprite(SpriteID id);

#endif //ASSETS_H
