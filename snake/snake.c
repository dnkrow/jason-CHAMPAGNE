#include "snake.h"

#include <stdlib.h>

bool point_equals(Point a, Point b)
{
    return a.x == b.x && a.y == b.y;
}

bool point_on_snake(Point p, Point snake[], int length)
{
    for (int i = 0; i < length; ++i)
    {
        if (point_equals(p, snake[i]))
        {
            return true;
        }
    }
    return false;
}

Point random_food(Point snake[], int length)
{
    Point food;
    do
    {
        food.x = (rand() % (BOARD_WIDTH - 2)) + 1;
        food.y = (rand() % (BOARD_HEIGHT - 2)) + 1;
    } while (point_on_snake(food, snake, length));
    return food;
}

Point move_snake(Point snake[], int length, Point new_head)
{
    Point old_tail = snake[length - 1];
    for (int i = length - 1; i > 0; --i)
    {
        snake[i] = snake[i - 1];
    }
    snake[0] = new_head;
    return old_tail;
}

void grow_snake(Point snake[], int *length, Point tail_segment)
{
    if (*length < MAX_SNAKE_LENGTH)
    {
        snake[*length] = tail_segment;
        (*length)++;
    }
}

