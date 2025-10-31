#ifndef RENDER_H
#define RENDER_H

#include <ncurses.h>
#include "snake.h"

void draw_border(void);
void draw_snake(Point snake[], int length);
void draw_food(Point food);
void draw_hud(int score);
void draw_game_over(int score);

#endif /* RENDER_H */

