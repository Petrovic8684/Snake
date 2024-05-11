#include "snake.h"

struct snake_element *snake = NULL;
enum movement_direction target_direction;

void initialize_snake(void)
{
    snake = (struct snake_element *)malloc(sizeof(struct snake_element));

    struct vector2 starting_position = {12, 12};
    snake->position = starting_position;

    snake->next_element = NULL;
}

void change_snake_direction(enum movement_direction direction)
{
    target_direction = direction;
}

void move_snake(void)
{
    switch (target_direction)
    {
    case UP:
        if (snake->position.y <= 0)
        {
            snake->position.y = GRID_DIMENSION - 1;
            return;
        }

        snake->position.y--;
        // move tail
        break;
    case DOWN:
        if (snake->position.y >= GRID_DIMENSION - 1)
        {
            snake->position.y = 0;
            return;
        }

        snake->position.y++;
        // move tail
        break;
    case LEFT:
        if (snake->position.x <= 0)
        {
            snake->position.x = GRID_DIMENSION - 2;
            return;
        }

        snake->position.x--;
        // move tail
        break;
    case RIGHT:
        if (snake->position.x >= GRID_DIMENSION - 2)
        {
            snake->position.x = 0;
            return;
        }

        snake->position.x++;
        // move tail
        break;
    }
}