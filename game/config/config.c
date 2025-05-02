#include <stdio.h>
#include "config.h"

#define min(a,b) (a > b ? b : a)

#define DEFAULT_WINDOW_WIDTH 500
#define DEFAULT_WINDOW_HEIGHT 650
#define DEFAULT_PADDING_SIZE 20
#define DEFAULT_CELL_SIZE min(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT)/3 - 2*DEFAULT_PADDING_SIZE/3

void init_config(WindowConfig* config) {
    if (config == NULL)
        return;

    config->window_height = DEFAULT_WINDOW_HEIGHT;
    config->window_width = DEFAULT_WINDOW_WIDTH;
    config->cell_size = DEFAULT_CELL_SIZE;
}
