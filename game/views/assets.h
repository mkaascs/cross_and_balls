#ifndef ASSETS_H
#define ASSETS_H
#include <SDL.h>
#include <stdbool.h>

SDL_Texture* cross_texture;
SDL_Texture* ball_texture;
SDL_Texture* restart_button_texture;
SDL_Texture* close_button_texture;
SDL_Texture* logo_texture;

void free_assets();
bool load_assets(SDL_Renderer*);

#endif //ASSETS_H
