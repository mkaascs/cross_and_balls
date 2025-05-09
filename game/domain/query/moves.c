#include <stdlib.h>
#include "moves.h"

#include "../../../memstat/memstat.h"

bool push(MoveQuery* query, MoveElement* move) {
    if (query == NULL || move == NULL)
        return false;

    if (query->tail != NULL) {
        MoveElement* current = query->tail;
        while (current->next != NULL)
            current = current->next;

        current->next = move;
        current->next->next = NULL;
    }

    else {
        query->tail = move;
        query->tail->next = NULL;
    }

    query->length++;
    return true;
}

MoveElement* pop(MoveQuery* query) {
    if (query == NULL)
        return NULL;

    if (query->tail == NULL)
        return NULL;

    MoveElement* tail = query->tail;
    query->tail = query->tail->next;
    query->length--;
    return tail;
}

void free_query(MoveQuery* query) {
    while (true) {
        MoveElement* move = pop(query);
        if (move == NULL)
            break;

        track_free((void**)&move);
    }

    track_free((void**)&query);
}