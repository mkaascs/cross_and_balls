#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#define NAME_LENGTH 32
#include <stdio.h>

typedef struct Gamer {
    char name[NAME_LENGTH];
    int score;
    struct Gamer* next;
} Gamer;

typedef struct {
    Gamer* head;
    Gamer* tail;
    int length;
} LeaderBoard;

LeaderBoard* init_leader_board();
LeaderBoard* init_leader_board_from_file(FILE*);
void add_gamer(LeaderBoard*, Gamer*);
void free_leader_board(LeaderBoard*);

#endif //LEADERBOARD_H
