#ifndef AI_H
#define AI_H
#include "../domain/entities/game.h"

typedef enum {
    BOT_DIFFICULTY_EASY,
    BOT_DIFFICULTY_MEDIUM,
    BOT_DIFFICULTY_HARD,
    BOT_DIFFICULTY_COUNT
} BotDifficulty;

void make_move_ai(Game* game);
void set_difficulty(BotDifficulty);
BotDifficulty get_current_difficulty();

#endif //AI_H
