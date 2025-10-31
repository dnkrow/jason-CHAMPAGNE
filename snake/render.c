#include "render.h"

void draw_border(void)
{
    for (int x = 0; x < BOARD_WIDTH; ++x)
    {
        mvaddch(0, x, '#');
        mvaddch(BOARD_HEIGHT - 1, x, '#');
    }
    for (int y = 0; y < BOARD_HEIGHT; ++y)
    {
        mvaddch(y, 0, '#');
        mvaddch(y, BOARD_WIDTH - 1, '#');
    }
}

void draw_snake(Point snake[], int length)
{
    mvaddch(snake[0].y, snake[0].x, 'O');
    for (int i = 1; i < length; ++i)
    {
        mvaddch(snake[i].y, snake[i].x, 'o');
    }
}

void draw_food(Point food)
{
    mvaddch(food.y, food.x, '*');
}

void draw_hud(int score)
{
    mvprintw(BOARD_HEIGHT, 0, "Score: %d  Quit: Q", score);
}

void draw_game_over(int score)
{
    mvprintw(BOARD_HEIGHT / 2, (BOARD_WIDTH - 20) / 2, "Game Over! Score: %d", score);
    mvprintw(BOARD_HEIGHT / 2 + 1, (BOARD_WIDTH - 24) / 2, "Press any key to exit...");
}

