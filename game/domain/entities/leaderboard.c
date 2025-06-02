#include "leaderboard.h"
#include "../../../memstat/memstat.h"

#include <string.h>

static int max(const int first, const int second) {
    return (first > second) ? first : second;
}

static int height(const GamerNode* node) {
    return node ? node->height : 0;
}

static void update_height(GamerNode* node) {
    if (node != NULL)
        node->height = 1 + max(height(node->left), height(node->right));
}

static int balance_factor(const GamerNode* node) {
    return node != NULL ? height(node->left) - height(node->right) : 0;
}

static GamerNode* rotate_right(GamerNode* y) {
    GamerNode* x = y->left;
    GamerNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    update_height(y);
    update_height(x);

    return x;
}

static GamerNode* rotate_left(GamerNode* x) {
    GamerNode* y = x->right;
    GamerNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    update_height(x);
    update_height(y);

    return y;
}

static GamerNode* balance(GamerNode* node) {
    update_height(node);
    int bf = balance_factor(node);

    if (bf > 1) {
        if (balance_factor(node->left) < 0)
            node->left = rotate_left(node->left);

        return rotate_right(node);
    }

    if (bf < -1) {
        if (balance_factor(node->right) > 0)
            node->right = rotate_right(node->right);

        return rotate_left(node);
    }

    return node;
}

static GamerNode* find_and_update(GamerNode* node, Gamer* gamer) {
    if (node == NULL)
        return NULL;

    int cmp = strcmp(gamer->name, node->gamer->name);
    if (cmp == 0) {
        node->gamer->score = gamer->score;
        return node;
    }

    GamerNode* found = find_and_update(node->left, gamer);
    if (found == NULL)
        found = find_and_update(node->right, gamer);

    return found;
}

static GamerNode* insert_node(GamerNode* node, Gamer* gamer) {
    if (node == NULL) {
        GamerNode* new_node = (GamerNode*)track_malloc(sizeof(GamerNode));
        new_node->gamer = gamer;
        new_node->left = new_node->right = NULL;
        new_node->height = 1;
        return new_node;
    }

    if (gamer->score > node->gamer->score ||
        (gamer->score == node->gamer->score && strcmp(gamer->name, node->gamer->name) < 0))
        node->left = insert_node(node->left, gamer);

    else node->right = insert_node(node->right, gamer);

    return balance(node);
}

LeaderBoard* init_leader_board() {
    LeaderBoard* lb = (LeaderBoard*)track_malloc(sizeof(LeaderBoard));
    lb->root = NULL;
    lb->length = 0;
    return lb;
}

void add_gamer(LeaderBoard* lb, Gamer* gamer) {
    if (lb == NULL || gamer == NULL)
        return;

    GamerNode* updated = find_and_update(lb->root, gamer);
    if (updated != NULL)
        return;

    Gamer* new_gamer = (Gamer*)track_malloc(sizeof(Gamer));
    strncpy(new_gamer->name, gamer->name, NAME_LENGTH);
    new_gamer->score = gamer->score;

    lb->root = insert_node(lb->root, new_gamer);
    lb->length++;
}

static void free_node(GamerNode* node) {
    if (node == NULL)
        return;

    free_node(node->left);
    free_node(node->right);
    track_free((void**)&node->gamer);
    track_free((void**)&node);
}

void free_leader_board(LeaderBoard* lb) {
    if (lb == NULL)
        return;

    free_node(lb->root);
    track_free((void**)&lb);
}

LeaderBoard* init_leader_board_from_file(FILE* file) {
    LeaderBoard* lb = init_leader_board();
    if (file == NULL)
        return lb;

    char line[128];
    while (fgets(line, sizeof(line), file)) {
        char name[NAME_LENGTH];
        int score;
        if (sscanf(line, " %31[^:]: %d", name, &score) == 2) {
            Gamer temp;
            strncpy(temp.name, name, NAME_LENGTH);
            temp.name[NAME_LENGTH - 1] = '\0';
            temp.score = score;
            add_gamer(lb, &temp);
        }
    }

    return lb;
}