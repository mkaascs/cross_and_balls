#include "leaderboard.h"

#include <string.h>

#include "../../../memstat/memstat.h"

LeaderBoard* init_leader_board() {
    LeaderBoard* leader_board = track_malloc(sizeof(LeaderBoard));
    leader_board->head = NULL;
    leader_board->tail = NULL;
    leader_board->length = 0;
    return leader_board;
}

LeaderBoard* init_leader_board_from_file(FILE* file) {
    if (file == NULL)
        return init_leader_board();

    LeaderBoard* leader_board = init_leader_board();
    char name[NAME_LENGTH];
    int score;
    while (fscanf(file, " %[^:]: %d", name, &score) == 2) {
        if (score < 0) score = 0;
        Gamer* gamer = track_malloc(sizeof(Gamer));
        strncpy(gamer->name, name, NAME_LENGTH - 1);
        gamer->name[NAME_LENGTH - 1] = '\0';
        gamer->score = score;
        gamer->next = NULL;

        if (leader_board->head == NULL) {
            leader_board->head = gamer;
            leader_board->tail = gamer;
        }

        else {
            leader_board->tail->next = gamer;
            leader_board->tail = gamer;
        }

        leader_board->length++;
    }

    return leader_board;
}

void add_gamer(LeaderBoard* leader_board, Gamer* gamer) {
    Gamer* current = leader_board->head;
    while (current) {
        if (strcmp(current->name, gamer->name) == 0) {
            current->score = gamer->score;
            return;
        }

        current = current->next;
    }

    if (leader_board->head == NULL) {
        leader_board->head = gamer;
        leader_board->tail = gamer;
    }

    else {
        leader_board->tail->next = gamer;
        leader_board->tail = gamer;
    }

    leader_board->length++;
}

void free_leader_board(LeaderBoard* leader_board) {
    Gamer* current = leader_board->head;
    while (current) {
        leader_board->head = current->next;
        track_free((void**)&current);
        current = leader_board->head;
    }

    track_free((void**)&leader_board);
}