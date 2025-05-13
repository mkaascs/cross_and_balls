#include "memstat.h"
#include <stdlib.h>
#include <string.h>

static Memstat memstat = {0};

void* track_malloc(size_t data_size) {
    memstat.malloc_count++;
    return malloc(data_size);
}

char* strdup_track(const char* str) {
    size_t len = strlen(str) + 1;
    char* copy = track_malloc(len);
    memcpy(copy, str, len);
    return copy;
}

void* track_calloc(size_t num, size_t data_size) {
    memstat.calloc_count++;
    return calloc(num, data_size);
}

void* track_realloc(void* pointer, size_t data_size) {
    memstat.realloc_count++;
    return realloc(pointer, data_size);
}

void track_free(void** pointer) {
    if (!pointer || !*pointer)
        return;

    memstat.free_count++;
    free(*pointer);
    pointer = NULL;
}

void get_memstat(Memstat* newMemstat) {
    *newMemstat = memstat;
}