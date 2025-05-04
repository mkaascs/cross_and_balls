#ifndef MOVES_H
#define MOVES_H

#include <stdbool.h>

typedef struct MoveElement {
    int position;
    struct MoveElement* next;
} MoveElement;

typedef struct {
    int length;
    MoveElement* tail;
} MoveQuery;

bool push(MoveQuery*, MoveElement*);
MoveElement* pop(MoveQuery*);
void free_query(MoveQuery*);

#endif //MOVES_H
