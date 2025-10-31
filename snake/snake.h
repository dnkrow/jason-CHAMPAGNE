#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>

#define BOARD_WIDTH 30
#define BOARD_HEIGHT 20
#define TICK_MSEC 120
#define MAX_SNAKE_LENGTH ((BOARD_WIDTH - 2) * (BOARD_HEIGHT - 2))

typedef struct
{
    int x;
    int y;
} Point;

bool point_equals(Point a, Point b);
bool point_on_snake(Point p, Point snake[], int length);
Point random_food(Point snake[], int length);
Point move_snake(Point snake[], int length, Point new_head);
void grow_snake(Point snake[], int *length, Point tail_segment);

#endif /* SNAKE_H */

