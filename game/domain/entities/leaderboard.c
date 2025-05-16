#include "leaderboard.h"

#include <string.h>

#include "../../../memstat/memstat.h"

static Gamer* merge(Gamer* a, Gamer* b) {
    if (a == NULL) return b;
    if (b == NULL) return a;

    Gamer* result = NULL;

    if (a->score >= b->score) {
        result = a;
        result->next = merge(a->next, b);
    } else {
        result = b;
        result->next = merge(a, b->next);
    }

    return result;
}

static void split(Gamer* source, Gamer** frontRef, Gamer** backRef) {
    Gamer* slow = source;
    Gamer* fast = source->next;

    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

static Gamer* merge_sort_gamers(Gamer* head) {
    if (head == NULL || head->next == NULL)
        return head;

    Gamer* a;
    Gamer* b;

    split(head, &a, &b);

    a = merge_sort_gamers(a);
    b = merge_sort_gamers(b);

    return merge(a, b);
}

void sort_leader_board(LeaderBoard* board) {
    if (board == NULL || board->head == NULL)
        return;

    board->head = merge_sort_gamers(board->head);

    Gamer* current = board->head;
    board->length = 0;
    while (current) {
        board->tail = current;
        current = current->next;
        board->length++;
    }
}

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

    sort_leader_board(leader_board);
    return leader_board;
}

void add_gamer(LeaderBoard* leader_board, Gamer* gamer) {
    Gamer* prev = NULL;
    Gamer* current = leader_board->head;

    while (current) {
        if (strcmp(current->name, gamer->name) == 0) {
            current->score = gamer->score;

            if (prev)
                prev->next = current->next;

            else leader_board->head = current->next;

            if (current == leader_board->tail)
                leader_board->tail = prev;

            break;
        }

        prev = current;
        current = current->next;
    }

    prev = NULL;
    current = leader_board->head;

    while (current && gamer->score < current->score) {
        prev = current;
        current = current->next;
    }

    gamer->next = current;

    if (prev)
        prev->next = gamer;

    else leader_board->head = gamer;


    if (current == NULL)
        leader_board->tail = gamer;

    Gamer* check = leader_board->head;
    int count = 0;
    while (check) {
        count++;
        check = check->next;
    }

    leader_board->length = count;
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