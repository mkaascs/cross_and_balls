#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#define NAME_LENGTH 32
#include <stdio.h>

typedef struct Gamer {
    char name[NAME_LENGTH];
    int score;
} Gamer;

typedef struct GamerNode {
    Gamer* gamer;
    int height;
    struct GamerNode* right;
    struct GamerNode* left;
} GamerNode;

typedef struct {
    GamerNode* root;
    int length;
} LeaderBoard;

LeaderBoard* init_leader_board();
LeaderBoard* init_leader_board_from_file(FILE*);
void add_gamer(LeaderBoard*, Gamer*);
void free_leader_board(LeaderBoard*);
void save_leader_board_to_file(FILE*, const LeaderBoard*);

#endif //LEADERBOARD_H
