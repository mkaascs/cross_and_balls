#include "session.h"

#include <string.h>

GameSession current_session;

void set_session(char name[NAME_LENGTH]) {
    memset(&current_session, 0, sizeof(GameSession));
    strncpy(current_session.gamer_name, name, NAME_LENGTH - 1);
    current_session.gamer_name[NAME_LENGTH - 1] = '\0';
}

GameSession* get_current_session() {
    return &current_session;
}