#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    unsigned int cell_size;
    unsigned int cell_padding;
    unsigned int cell_left;
    unsigned int cell_top;

    unsigned int restart_button_width;
    unsigned int restart_button_height;
    unsigned int restart_button_x;
    unsigned int restart_button_y;
} BoardLayout;

typedef struct {
    unsigned int logo_x;
    unsigned int logo_y;
    unsigned int logo_width;
    unsigned int logo_height;
} MenuLayout;

typedef struct {
    unsigned int window_width;
    unsigned int window_height;

    unsigned int padding_left;
    unsigned int padding_top;

    unsigned int close_button_x;
    unsigned int close_button_y;
    unsigned int close_button_width;
    unsigned int close_button_height;

    BoardLayout board;
    MenuLayout menu;
} WindowLayout;

WindowLayout* init_window_layout();

#endif //CONFIG_H
