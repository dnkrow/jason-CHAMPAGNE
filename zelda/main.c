// Zelda-like terminal game entry point
#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"

int main(void) {
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
    nodelay(stdscr, TRUE);
    // Enable mouse clicks (left/right)
    mousemask(BUTTON1_PRESSED | BUTTON1_CLICKED | BUTTON3_PRESSED | BUTTON3_CLICKED, NULL);

    // Seed RNG
    srand((unsigned)time(NULL));

    Game game;
    game_init(&game);

    struct timespec ts_prev; timespec_get(&ts_prev, TIME_UTC);

    int running = 1;
    while (running && !game.quit) {
        struct timespec ts_now; timespec_get(&ts_now, TIME_UTC);
        double dt = (ts_now.tv_sec - ts_prev.tv_sec) + (ts_now.tv_nsec - ts_prev.tv_nsec) / 1e9;
        if (dt > 0.1) dt = 0.1; // clamp big frames
        ts_prev = ts_now;

        int ch;
        MEVENT me;
        game.input.left_click = 0;
        game.input.right_click = 0;
        game.input.mouse_world_x = -1;
        game.input.mouse_world_y = -1;

        for (int i = 0; i < 8; ++i) game.input.key[i] = 0;

        // Poll inputs (non-blocking)
        while ((ch = getch()) != ERR) {
            if (ch == KEY_MOUSE) {
                if (getmouse(&me) == OK) {
                    int view_h = getmaxy(stdscr) - 2;
                    if (me.y < view_h) {
                        // Convert screen coords to world coords using camera
                        int world_x = game.camera_x + me.x;
                        int world_y = game.camera_y + me.y;
                        game.input.mouse_world_x = world_x;
                        game.input.mouse_world_y = world_y;
                        if (me.bstate & (BUTTON1_PRESSED | BUTTON1_CLICKED)) {
                            game.input.left_click = 1;
                        }
                        if (me.bstate & (BUTTON3_PRESSED | BUTTON3_CLICKED)) {
                            game.input.right_click = 1;
                        }
                    }
                }
            } else if (ch == KEY_UP) {
                game.input.key[INPUT_UP] = 1;
            } else if (ch == KEY_DOWN) {
                game.input.key[INPUT_DOWN] = 1;
            } else if (ch == KEY_LEFT) {
                game.input.key[INPUT_LEFT] = 1;
            } else if (ch == KEY_RIGHT) {
                game.input.key[INPUT_RIGHT] = 1;
            } else if (ch == 'e' || ch == 'E') {
                game.input.key[INPUT_INTERACT] = 1;
            } else if (ch == 'q' || ch == 'Q') {
                running = 0;
                break;
            }
        }

        game_update(&game, dt);
        game_render(&game);

        // Frame cap ~60 FPS
        napms(16);
    }

    endwin();
    return 0;
}
