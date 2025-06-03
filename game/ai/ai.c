#include "ai.h"
#include <stdlib.h>
#include <time.h>

static const uint16_t WIN_PATTERNS[] = {
    0b111000000, 0b000111000, 0b000000111,
    0b100100100, 0b010010010, 0b001001001,
    0b100010001, 0b001010100
};

static BotDifficulty bot_difficulty = BOT_DIFFICULTY_MEDIUM;

void ai_init() {
    srand(time(NULL));
}

static int find_winning_move(uint16_t player_mask, uint16_t empty_mask) {
    for (int i = 0; i < 8; i++) {
        uint16_t win = WIN_PATTERNS[i];
        if (__builtin_popcount(player_mask & win) == 2) {
            uint16_t pos = win & empty_mask;
            if (__builtin_popcount(pos) == 1) {
                for (int j = 0; j < 9; j++)
                    if (pos & (1 << j))
                        return j;
            }
        }
    }

    return -1;
}

static bool is_empty(Game* game, int pos) {
    uint16_t mask = (1 << pos);
    return !(game->crosses_moves & mask) && !(game->balls_moves & mask);
}

static int get_random_move(uint16_t empty_mask) {
    int available[9];
    int count = 0;

    for (int i = 0; i < 9; i++) {
        if (empty_mask & (1 << i)) {
            available[count++] = i;
        }
    }

    return count > 0 ? available[rand() % count] : -1;
}

void set_difficulty(BotDifficulty difficulty) {
    bot_difficulty = difficulty;
}

BotDifficulty get_current_difficulty() {
    return bot_difficulty;
}

void make_move_ai(Game* game) {
    if (game == NULL || game->is_complete)
        return;

    uint16_t bot_moves = game->last_move == Ball ? game->crosses_moves : game->balls_moves;
    uint16_t human_moves = game->last_move == Ball ? game->balls_moves : game->crosses_moves;
    uint16_t empty = ~(bot_moves | human_moves) & 0x1FF;

    int move = -1;

    // Уровень сложности: Легкий
    if (bot_difficulty == BOT_DIFFICULTY_EASY) {
        // 50% случайный ход, 50% попытка выиграть/блокировать
        if (rand() % 2 == 0) {
            move = get_random_move(empty);
            if (move >= 0) {
                game->make_move(game, move);
                return;
            }
        }
    }

    // Для всех уровней сложности проверяем выигрышные ходы
    move = find_winning_move(bot_moves, empty);
    if (move >= 0) { game->make_move(game, move); return; }

    // Для среднего и сложного уровней блокируем игрока
    if (bot_difficulty >= BOT_DIFFICULTY_MEDIUM) {
        move = find_winning_move(human_moves, empty);
        if (move >= 0) { game->make_move(game, move); return; }
    }

    // Уровень сложности: Легкий - случайный ход
    if (bot_difficulty == BOT_DIFFICULTY_EASY) {
        move = get_random_move(empty);
        if (move >= 0) { game->make_move(game, move); return; }
    }

    // Уровень сложности: Средний
    else if (bot_difficulty == BOT_DIFFICULTY_MEDIUM || bot_difficulty == BOT_DIFFICULTY_SPECIAL_MODE) {
        // Центр или углы с вероятностью 70%
        if (rand() % 10 < 7) {
            if (is_empty(game, 4)) { game->make_move(game, 4); return; }

            int corners[] = {0, 2, 6, 8};
            for (int i = 0; i < 4; i++) {
                if (is_empty(game, corners[i])) {
                    game->make_move(game, corners[i]);
                    return;
                }
            }
        }
        // Случайный ход с вероятностью 30%
        move = get_random_move(empty);
        if (move >= 0) { game->make_move(game, move); return; }
    }

    // Уровень сложности: Сложный
    else if (bot_difficulty == BOT_DIFFICULTY_HARD) {
        // Всегда занимаем центр если свободен
        if (is_empty(game, 4)) { game->make_move(game, 4); return; }

        // Пытаемся создать вилку (две выигрышные возможности)
        for (int i = 0; i < 9; i++) {
            if (is_empty(game, i)) {
                uint16_t new_bot_moves = bot_moves | (1 << i);
                int win_count = 0;
                for (int j = 0; j < 8; j++) {
                    uint16_t win = WIN_PATTERNS[j];
                    if (__builtin_popcount(new_bot_moves & win) == 2 &&
                        (empty & win) == (1 << i)) {
                        win_count++;
                        if (win_count >= 2) {
                            game->make_move(game, i);
                            return;
                        }
                        }
                }
            }
        }

        // Блокируем вилки игрока
        for (int i = 0; i < 9; i++) {
            if (is_empty(game, i)) {
                uint16_t new_human_moves = human_moves | (1 << i);
                int win_count = 0;
                for (int j = 0; j < 8; j++) {
                    uint16_t win = WIN_PATTERNS[j];
                    if (__builtin_popcount(new_human_moves & win) == 2 &&
                        (empty & win) == (1 << i)) {
                        win_count++;
                        if (win_count >= 2) {
                            game->make_move(game, i);
                            return;
                        }
                        }
                }
            }
        }

        // Занимаем углы если свободны
        int corners[] = {0, 2, 6, 8};
        for (int i = 0; i < 4; i++) {
            if (is_empty(game, corners[i])) {
                game->make_move(game, corners[i]);
                return;
            }
        }
    }

    // Резервный вариант - первый доступный ход
    for (int i = 0; i < 9; i++) {
        if (is_empty(game, i)) {
            game->make_move(game, i);
            return;
        }
    }
}