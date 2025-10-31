#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "render.h"
#include "snake.h"

int main(void)
{
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

	for (int i = 0; i < snake_length; ++i)
	{
		snake[i].x = BOARD_WIDTH / 2 - i;
		snake[i].y = BOARD_HEIGHT / 2;
	}

	Point food = random_food(snake, snake_length);
	int score = 0;
	bool running = true;

	while (running)
	{
		int ch = getch();
		switch (ch)
		{
		case KEY_UP:
		case 'w':
		case 'W':
			if (dy != 1)
			{
				dx = 0;
				dy = -1;
			}
			break;
		case KEY_DOWN:
		case 's':
		case 'S':
			if (dy != -1)
			{
				dx = 0;
				dy = 1;
			}
			break;
		case KEY_LEFT:
		case 'a':
		case 'A':
			if (dx != 1)
			{
				dx = -1;
				dy = 0;
			}
			break;
		case KEY_RIGHT:
		case 'd':
		case 'D':
			if (dx != -1)
			{
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

		Point new_head = {snake[0].x + dx, snake[0].y + dy};

		if (new_head.x <= 0 || new_head.x >= BOARD_WIDTH - 1 ||
			new_head.y <= 0 || new_head.y >= BOARD_HEIGHT - 1 ||
			point_on_snake(new_head, snake, snake_length))
		{
			running = false;
			break;
		}

		Point old_tail = move_snake(snake, snake_length, new_head);

		if (point_equals(new_head, food))
		{
			grow_snake(snake, &snake_length, old_tail);
			score += 10;
			food = random_food(snake, snake_length);
		}

		clear();
		draw_border();
		draw_food(food);
		draw_snake(snake, snake_length);
		draw_hud(score);

		refresh();
		napms(TICK_MSEC);
	}

	nodelay(stdscr, false);
	draw_game_over(score);
	refresh();
	getch();

	endwin();
	return 0;
}
