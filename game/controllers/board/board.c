#include "../controllers.h"
#include "../states.h"
#include "../../views/board/views.h"
#include "../../../memstat/memstat.h"
#include "../../ai/ai.h"
#include "../../session/session.h"

static int get_step_position(const BoardLayout layout, int x, int y) {
    if (x < layout.cell.margin_x ||
        x > layout.cell.margin_x + 3 * layout.cell.width ||
        y < layout.cell.margin_y ||
        y > layout.cell.margin_y + 3 * layout.cell.height)
        return -1;


    int col = (x - layout.cell.margin_x) / layout.cell.width;
    int row = (y - layout.cell.margin_y) / layout.cell.height;

    if (col < 0 || col > 2 || row < 0 || row > 2)
        return -1;

    return row * 3 + col;
}

static void update_leaderboard(LeaderBoard* leader_board, int score) {
    GameSession* session = get_current_session();
    if (strlen(session->gamer_name) == 0)
        return;

    Gamer gamer;
    strncpy(gamer.name, session->gamer_name, NAME_LENGTH);
    gamer.name[NAME_LENGTH - 1] = '\0';
    gamer.score = score;

    add_gamer(leader_board, &gamer);
}

static bool is_on_element_click(ElementLayout element, int x, int y) {
    return x >= element.margin_x && x <= element.margin_x + element.width &&
        y >= element.margin_y && y <= element.margin_y + element.height;
}

static void on_restart_button_click(const BoardController* this) {
    this->game->reset(this->game);
}

static void on_close_button_click(const BoardController* this) {
    update_leaderboard(this->leader_board, this->game->score.cross_score);

    this->game->score.cross_score = 0;
    this->game->score.ball_score = 0;
    this->game->reset(this->game);
    this->change_state(MODE_SCREEN);
}

static void on_click(const BoardController* this, int x, int y) {
    if (is_on_element_click(this->layout.close_button, x, y)) {
        on_close_button_click(this);
        return;
    }

    if (is_on_element_click(this->layout.board.restart_button, x, y)) {
        on_restart_button_click(this);
        return;
    }

    int position = get_step_position(this->layout.board, x, y);
    if (position == -1) return;

    if (!this->game->make_move(this->game, position))
        return;

    if (this->game->check_win(this->game)) {
        if (this->game->last_move == Cross)
            this->game->score.cross_score++;
        else
            this->game->score.ball_score++;
        return;
    }

    if (!this->game->is_complete) {
        make_move_ai(this->game);
        if (this->game->check_win(this->game)) {
            if (this->game->last_move == Cross)
                this->game->score.cross_score++;
            else
                this->game->score.ball_score++;
        }
    }

    this->game->check_draw(this->game);
}

static void on_update(const BoardController* this, SDL_Renderer* renderer) {
    draw_board(renderer, *this->game, this->layout, get_current_difficulty() == BOT_DIFFICULTY_SPECIAL_MODE);
}

BoardController* init_board_controller(WindowLayout layout, Game* game, LeaderBoard* leader_board, void (*change_state)(StateScreen)) {
    BoardController* controller = track_malloc(sizeof(BoardController));
    controller->change_state = change_state;
    controller->game = game;
    controller->leader_board = leader_board;
    controller->layout = layout;
    controller->on_click = on_click;
    controller->on_update = on_update;

    return controller;
}