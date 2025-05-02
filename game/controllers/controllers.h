#ifndef BOARD_CONTROLLER_H
#define BOARD_CONTROLLER_H

#include "../domain/game.h"
#include "../views/window/size.h"

typedef struct BoardController {
    Game* game;
    WindowSize size;
    void (*on_click)(struct BoardController* this, int x, int y);
} BoardController;

BoardController* init_controller(WindowSize, Game*);

#endif //BOARD_CONTROLLER_H
