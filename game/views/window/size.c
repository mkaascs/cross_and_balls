#include <stdlib.h>
#include "size.h"

#define DEFAULT_WINDOW_WIDTH 500
#define DEFAULT_WINDOW_HEIGHT 650
#define DEFAULT_PADDING_LEFT 20
#define DEFAULT_PADDING_TOP 20
#define DEFAULT_CELL_PADDING 20

WindowSize* init_window_size() {
    WindowSize* size = malloc(sizeof(WindowSize));

    size->window_height = DEFAULT_WINDOW_HEIGHT;
    size->window_width = DEFAULT_WINDOW_WIDTH;

    size->cell_size = DEFAULT_WINDOW_WIDTH > DEFAULT_WINDOW_HEIGHT
        ? DEFAULT_WINDOW_HEIGHT / 3 - 2 * DEFAULT_PADDING_TOP / 3
        : DEFAULT_WINDOW_WIDTH / 3 - 2 * DEFAULT_PADDING_LEFT / 3;

    size->padding_left = DEFAULT_PADDING_LEFT;
    size->padding_top = DEFAULT_PADDING_TOP;

    size->cell_padding = DEFAULT_CELL_PADDING;
    return size;
}
