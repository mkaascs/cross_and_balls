#include "layout.h"

#include "../../../memstat/memstat.h"

#define DEFAULT_WINDOW_WIDTH 500
#define DEFAULT_WINDOW_HEIGHT 625

#define DEFAULT_PADDING_LEFT 20
#define DEFAULT_PADDING_TOP 20

#define DEFAULT_CELL_PADDING 20

#define RESTART_BUTTON_WIDTH 116
#define RESTART_BUTTON_HEIGHT 42

#define CLOSE_BUTTON_WIDTH 38
#define CLOSE_BUTTON_HEIGHT 37

#define LOGO_WIDTH 300

WindowLayout* init_window_layout() {
    WindowLayout* size = track_malloc(sizeof(WindowLayout));

    size->window_height = DEFAULT_WINDOW_HEIGHT;
    size->window_width = DEFAULT_WINDOW_WIDTH;

    size->padding_left = DEFAULT_PADDING_LEFT;
    size->padding_top = DEFAULT_PADDING_TOP;

    size->board.cell_padding = DEFAULT_CELL_PADDING;
    size->board.cell_size = DEFAULT_WINDOW_WIDTH > DEFAULT_WINDOW_HEIGHT
       ? DEFAULT_WINDOW_HEIGHT / 3 - 2 * DEFAULT_PADDING_TOP / 3
       : DEFAULT_WINDOW_WIDTH / 3 - 2 * DEFAULT_PADDING_LEFT / 3;

    size->board.cell_left = (DEFAULT_WINDOW_WIDTH - size->board.cell_size * 3) / 2;
    size->board.cell_top = (DEFAULT_WINDOW_HEIGHT - size->board.cell_size * 3) / 2;

    size->board.restart_button_width = RESTART_BUTTON_WIDTH;
    size->board.restart_button_height = RESTART_BUTTON_HEIGHT;
    size->board.restart_button_x = (DEFAULT_WINDOW_WIDTH - RESTART_BUTTON_WIDTH) / 2;
    size->board.restart_button_y = size->board.cell_top + size->board.cell_size * 3 + RESTART_BUTTON_HEIGHT / 2;

    size->close_button_width = CLOSE_BUTTON_WIDTH;
    size->close_button_height = CLOSE_BUTTON_HEIGHT;
    size->close_button_x = DEFAULT_PADDING_LEFT;
    size->close_button_y = DEFAULT_PADDING_TOP;

    size->menu.logo_width = LOGO_WIDTH;
    size->menu.logo_height = size->menu.logo_width * 5 / 7;
    size->menu.logo_x = (DEFAULT_WINDOW_WIDTH - LOGO_WIDTH) / 2;
    size->menu.logo_y = DEFAULT_PADDING_TOP;

    return size;
}
