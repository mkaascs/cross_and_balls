#ifndef INPUT_BOX_H
#define INPUT_BOX_H

#include "SDL.h"
#include <SDL_ttf.h>
#include <stdbool.h>
#include "../layout/layout.h"

#define INPUTBOX_MAX_LENGTH 32

typedef struct {
    char text[INPUTBOX_MAX_LENGTH + 1];
    int length;
    bool active;

    SDL_Rect rect;
    TTF_Font* font;
    SDL_Color text_color;
    SDL_Color bg_color;
    SDL_Color border_color;
} InputBox;

void init_input_box(InputBox* box, WindowLayout layout);
void render_input_box(InputBox* box, SDL_Renderer* renderer);

#endif //INPUT_BOX_H
