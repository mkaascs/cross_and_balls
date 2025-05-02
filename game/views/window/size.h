#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    unsigned int window_width;
    unsigned int window_height;
    unsigned int cell_size;
} WindowSize;

WindowSize* init_window_size();

#endif //CONFIG_H
