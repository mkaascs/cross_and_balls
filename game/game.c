#include "game.h"

#define WIN_PATTERNS_COUNT 8

Game* game;
const uint16_t WIN_PATTERNS[WIN_PATTERNS_COUNT] = {
    0b111000000, 0b000111000, 0b000000111,
    0b100100100, 0b010010010, 0b001001001,
    0b100010001, 0b001010100
};

bool checkWin() {
    uint16_t currentPlayer = game->lastMove == Cross
        ? game->crossesMoves
        : game->ballsMoves;

    for (int index = 0; index < WIN_PATTERNS_COUNT; index++) {
        if ((currentPlayer & WIN_PATTERNS[index]) == WIN_PATTERNS[index])
            return true;
    }

    return false;
}

bool makeMove(int position) {
    if (position < 0 || position > 9)
        return false;

    uint16_t mask = 1 << position;
    if ((game->crossesMoves | game->ballsMoves) & mask)
        return false;

    if (game->lastMove == Cross)
        game->ballsMoves |= mask;

    else game->crossesMoves |= mask;

    game->lastMove = !game->lastMove;
    return true;
}

void runGame(Game* newGame) {
    newGame->lastMove = Ball;

    newGame->crossesMoves = 0;
    newGame->ballsMoves = 0;

    newGame->checkWin = checkWin;
    newGame->makeMove = makeMove;

    game = newGame;
}