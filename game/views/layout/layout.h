#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    unsigned int window_width;
    unsigned int window_height;

    unsigned int padding_left;
    unsigned int padding_top;

    unsigned int cell_size;
    unsigned int cell_padding;
    unsigned int cell_left;
    unsigned int cell_top;

    unsigned int restart_button_width;
    unsigned int restart_button_height;
    unsigned int restart_button_x;
    unsigned int restart_button_y;
} WindowLayout;

WindowLayout* init_window_layout();

#endif //CONFIG_H
