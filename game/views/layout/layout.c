#include "layout.h"
#include <stdlib.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

WindowLayout* init_window_layout(unsigned int width, unsigned int height) {
    WindowLayout* layout = malloc(sizeof(WindowLayout));
    if (!layout) return NULL;

    update_window_layout(layout, width, height);
    return layout;
}

void update_window_layout(WindowLayout* layout, unsigned int width, unsigned int height) {
    if (!layout) return;

    layout->window_width = width;
    layout->window_height = height;

    const float min_dim = MIN(width, height);
    const float base_unit = min_dim / 20.0f;
    const float padding = base_unit * 0.5f;

    // Закрывающая кнопка
    layout->close_button.width = 1.4f * base_unit;
    layout->close_button.height = 1.4f * base_unit;
    layout->close_button.margin_x = padding;
    layout->close_button.margin_y = padding;
    layout->close_button.padding = base_unit * 0.05f;

    // Игровое поле
    const float board_size = min_dim * 0.8f;
    const float cell_size = board_size / 3.0f;
    layout->board.cell.width = cell_size;
    layout->board.cell.height = cell_size;
    layout->board.cell.margin_x = (width - board_size) / 2;
    layout->board.cell.margin_y = (height - board_size) / 2 - base_unit;
    layout->board.cell.padding = cell_size * 0.15f; // 15% от размера ячейки

    // Кнопка рестарта
    layout->board.restart_button.width = 5.5f * base_unit;
    layout->board.restart_button.height = 1.8f * base_unit;
    layout->board.restart_button.margin_x = (width - layout->board.restart_button.width) / 2;
    layout->board.restart_button.margin_y = layout->board.cell.margin_y + board_size + base_unit;
    layout->board.restart_button.padding = base_unit * 0.3f;

    // Меню
    layout->menu.logo.width = min_dim * 0.7f;
    layout->menu.logo.height = layout->menu.logo.width * 0.65f;
    layout->menu.logo.margin_x = (width - layout->menu.logo.width) / 2;
    layout->menu.logo.margin_y = base_unit * 3;
    layout->menu.logo.padding = base_unit * 0.1f;

    layout->menu.button.width = min_dim * 0.55f;
    layout->menu.button.height = base_unit * 1.8f;
    layout->menu.button.margin_x = (width - layout->menu.button.width) / 2;

    // Позиция первой кнопки
    const float first_button_y = layout->menu.logo.margin_y + layout->menu.logo.height + base_unit * 2;
    layout->menu.button.margin_y = first_button_y;
    layout->menu.button_spacing = base_unit * 1.5f;

    // Таблица лидеров
    layout->leaderboard.font_size = base_unit * 0.7f;
    layout->leaderboard.row_height = base_unit * 2.0f;
    layout->leaderboard.margin_x = (width - min_dim * 0.7f) / 2;
    layout->leaderboard.margin_y = base_unit * 4;
    layout->leaderboard.max_players = 8;
}