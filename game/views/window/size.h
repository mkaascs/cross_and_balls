#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    unsigned int window_width;
    unsigned int window_height;
    unsigned int cell_size;

    unsigned int padding_left;
    unsigned int padding_top;

    unsigned int cell_padding;
} WindowSize;

WindowSize* init_window_size();

#endif //CONFIG_H
