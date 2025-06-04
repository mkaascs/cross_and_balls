#ifndef SESSION_H
#define SESSION_H

#define NAME_LENGTH 32

typedef struct GameSession {
    char gamer_name[NAME_LENGTH];
} GameSession;

void set_session(char name[NAME_LENGTH]);
GameSession* get_current_session();

#endif //SESSION_H
