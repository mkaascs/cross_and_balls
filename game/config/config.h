#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    unsigned int window_width;
    unsigned int window_height;
    unsigned int cell_size;
} WindowConfig;

void init_config(WindowConfig* config);

#endif //CONFIG_H
