#ifndef BUTTON_H
#define BUTTON_H
#include <SDL_rect.h>

typedef struct {
    SDL_Rect rect;
    const char* label;
    void (*on_click)(void);
} Button;

#endif //BUTTON_H
