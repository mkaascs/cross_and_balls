#ifndef MEMSTAT_H
#define MEMSTAT_H
#include <sys/_types/_size_t.h>

typedef struct {
    size_t malloc_count;
    size_t calloc_count;
    size_t realloc_count;
    size_t free_count;
} Memstat;

void* track_malloc(size_t);
void* track_calloc(size_t, size_t);
void* track_realloc(void*, size_t);
char* strdup_track(const char*);
void track_free(void**);
void get_memstat(Memstat*);

#endif //MEMSTAT_H
