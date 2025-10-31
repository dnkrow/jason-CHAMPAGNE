#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int x;
    int y;
} Point;

static const int BOARD_WIDTH = 30;
static const int BOARD_HEIGHT = 20;
static const int TICK_MSEC = 120;
static const int MAX_SNAKE_LENGTH = (BOARD_WIDTH - 2) * (BOARD_HEIGHT - 2);

static bool point_equals(Point a, Point b) {
    return a.x == b.x && a.y == b.y;
}

static bool point_on_snake(Point p, Point snake[], int length) {
    for (int i = 0; i < length; ++i) {
        if (point_equals(p, snake[i])) {
            return true;
        }
    }
    return false;
}

static Point random_food(Point snake[], int length) {
    Point food;
    do {
        food.x = (rand() % (BOARD_WIDTH - 2)) + 1;
        food.y = (rand() % (BOARD_HEIGHT - 2)) + 1;
    } while (point_on_snake(food, snake, length));
    return food;
}

static void draw_border(void) {
    for (int x = 0; x < BOARD_WIDTH; ++x) {
        mvaddch(0, x, '#');
        mvaddch(BOARD_HEIGHT - 1, x, '#');
    }
    for (int y = 0; y < BOARD_HEIGHT; ++y) {
        mvaddch(y, 0, '#');
        mvaddch(y, BOARD_WIDTH - 1, '#');
    }
}

static void draw_snake(Point snake[], int length) {
    mvaddch(snake[0].y, snake[0].x, 'O');
    for (int i = 1; i < length; ++i) {
        mvaddch(snake[i].y, snake[i].x, 'o');
    }
}

static void draw_food(Point food) {
    mvaddch(food.y, food.x, '*');
}

int main(void) {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, true);
    nodelay(stdscr, true);

    srand((unsigned int)time(NULL));

    Point snake[MAX_SNAKE_LENGTH];
    int snake_length = 4;
    int dx = 1;
    int dy = 0;

    for (int i = 0; i < snake_length; ++i) {
        snake[i].x = BOARD_WIDTH / 2 - i;
        snake[i].y = BOARD_HEIGHT / 2;
    }

    Point food = random_food(snake, snake_length);
    int score = 0;
    bool running = true;

    while (running) {
        int ch = getch();
        switch (ch) {
            case KEY_UP:
            case 'w':
            case 'W':
                if (dy != 1) {
                    dx = 0;
                    dy = -1;
                }
                break;
            case KEY_DOWN:
            case 's':
            case 'S':
                if (dy != -1) {
                    dx = 0;
                    dy = 1;
                }
                break;
            case KEY_LEFT:
            case 'a':
            case 'A':
                if (dx != 1) {
                    dx = -1;
                    dy = 0;
                }
                break;
            case KEY_RIGHT:
            case 'd':
            case 'D':
                if (dx != -1) {
                    dx = 1;
                    dy = 0;
                }
                break;
            case 'q':
            case 'Q':
                running = false;
                continue;
            default:
                break;
        }

        Point new_head = { snake[0].x + dx, snake[0].y + dy };

        if (new_head.x <= 0 || new_head.x >= BOARD_WIDTH - 1 ||
            new_head.y <= 0 || new_head.y >= BOARD_HEIGHT - 1 ||
            point_on_snake(new_head, snake, snake_length)) {
            running = false;
            break;
        }

        Point old_tail = snake[snake_length - 1];
        for (int i = snake_length - 1; i > 0; --i) {
            snake[i] = snake[i - 1];
        }
        snake[0] = new_head;

        if (point_equals(new_head, food)) {
            if (snake_length < MAX_SNAKE_LENGTH) {
                snake[snake_length] = old_tail;
                snake_length++;
            }
            score += 10;
            food = random_food(snake, snake_length);
        }

        clear();
        draw_border();
        draw_food(food);
        draw_snake(snake, snake_length);
        mvprintw(BOARD_HEIGHT, 0, "Score: %d  Quit: Q", score);

        refresh();
        napms(TICK_MSEC);
    }

    nodelay(stdscr, false);
    mvprintw(BOARD_HEIGHT / 2, (BOARD_WIDTH - 20) / 2, "Game Over! Score: %d", score);
    mvprintw(BOARD_HEIGHT / 2 + 1, (BOARD_WIDTH - 24) / 2, "Press any key to exit...");
    refresh();
    getch();

    endwin();
    return 0;
}
