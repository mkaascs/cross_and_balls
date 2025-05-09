#include "assets.h"

extern SDL_Texture* cross_texture = NULL;
extern SDL_Texture* ball_texture = NULL;
extern SDL_Texture* restart_button_texture = NULL;

bool load_assets(SDL_Renderer* renderer) {
    SDL_Surface* cross_surface = SDL_LoadBMP("assets/sprites/cross.bmp");
    if (cross_surface == NULL)
        return false;

    SDL_Surface* ball_surface = SDL_LoadBMP("assets/sprites/ball.bmp");
    if (ball_surface == NULL) {
        SDL_FreeSurface(cross_surface);
        return false;
    }

    SDL_Surface* restart_button_surface = SDL_LoadBMP("assets/sprites/button_restart.bmp");
    if (restart_button_surface == NULL) {
        SDL_FreeSurface(cross_surface);
        SDL_FreeSurface(ball_surface);
        return false;
    }

    cross_texture = SDL_CreateTextureFromSurface(renderer, cross_surface);
    ball_texture = SDL_CreateTextureFromSurface(renderer, ball_surface);
    restart_button_texture = SDL_CreateTextureFromSurface(renderer, restart_button_surface);
    SDL_FreeSurface(cross_surface);
    SDL_FreeSurface(ball_surface);
    SDL_FreeSurface(restart_button_surface);

    return cross_texture && ball_texture && restart_button_texture;
}

void free_assets() {
    if (cross_texture) SDL_DestroyTexture(cross_texture);
    if (ball_texture) SDL_DestroyTexture(ball_texture);
    if (restart_button_texture) SDL_DestroyTexture(restart_button_texture);
    cross_texture = NULL;
    ball_texture = NULL;
    restart_button_texture = NULL;
}