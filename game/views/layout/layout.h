#ifndef LAYOUT_H
#define LAYOUT_H

typedef struct {
    float width;
    float height;
    float margin_x;
    float margin_y;
    float padding;
} ElementLayout;

typedef struct {
    ElementLayout cell;
    ElementLayout restart_button;
} BoardLayout;

typedef struct {
    ElementLayout logo;
    ElementLayout button;
    ElementLayout input_box;
    unsigned int font_size;
    float button_spacing;
} MenuLayout;

typedef struct {
    ElementLayout button;
    float button_spacing;
} ModeLayout;

typedef struct {
    float font_size;
    float row_height;
    float margin_x;
    float margin_y;
    unsigned int max_players;
} LeaderboardLayout;

typedef struct {
    unsigned int window_width;
    unsigned int window_height;

    ElementLayout close_button;

    BoardLayout board;
    MenuLayout menu;
    LeaderboardLayout leaderboard;
    ModeLayout mode;
} WindowLayout;

WindowLayout* init_window_layout(unsigned int width, unsigned int height);
void update_window_layout(WindowLayout* layout, unsigned int width, unsigned int height);

#endif // LAYOUT_H