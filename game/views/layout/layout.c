#include <stdlib.h>
#include "layout.h"

#define DEFAULT_WINDOW_WIDTH 500
#define DEFAULT_WINDOW_HEIGHT 625

#define DEFAULT_PADDING_LEFT 20
#define DEFAULT_PADDING_TOP 20

#define DEFAULT_CELL_PADDING 20

#define RESTART_BUTTON_WIDTH 116
#define RESTART_BUTTON_HEIGHT 42

WindowLayout* init_window_layout() {
    WindowLayout* size = malloc(sizeof(WindowLayout));

    size->window_height = DEFAULT_WINDOW_HEIGHT;
    size->window_width = DEFAULT_WINDOW_WIDTH;

    size->padding_left = DEFAULT_PADDING_LEFT;
    size->padding_top = DEFAULT_PADDING_TOP;

    size->cell_padding = DEFAULT_CELL_PADDING;
    size->cell_size = DEFAULT_WINDOW_WIDTH > DEFAULT_WINDOW_HEIGHT
       ? DEFAULT_WINDOW_HEIGHT / 3 - 2 * DEFAULT_PADDING_TOP / 3
       : DEFAULT_WINDOW_WIDTH / 3 - 2 * DEFAULT_PADDING_LEFT / 3;

    size->cell_left = (DEFAULT_WINDOW_WIDTH - size->cell_size * 3) / 2;
    size->cell_top = (DEFAULT_WINDOW_HEIGHT - size->cell_size * 3) / 2;

    size->restart_button_width = RESTART_BUTTON_WIDTH;
    size->restart_button_height = RESTART_BUTTON_HEIGHT;
    size->restart_button_x = (DEFAULT_WINDOW_WIDTH - RESTART_BUTTON_WIDTH) / 2;
    size->restart_button_y = size->cell_top + size->cell_size * 3 + RESTART_BUTTON_HEIGHT / 2;

    return size;
}
