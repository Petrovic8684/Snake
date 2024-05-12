#include "snake.h"

struct snake_element *snake = NULL;
enum movement_direction target_direction = DOWN;

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
    Uint8 previous_x = snake->position.x;
    Uint8 previous_y = snake->position.y;

    Uint8 save_x;
    Uint8 save_y;

    // Moves the head and changes target direction
    switch (target_direction)
    {
    case UP:
        if (snake->position.y <= 0)
        {
            snake->position.y = GRID_DIMENSION - 1;
            return;
        }

        snake->position.y--;
        break;
    case DOWN:
        if (snake->position.y >= GRID_DIMENSION - 1)
        {
            snake->position.y = 0;
            return;
        }

        snake->position.y++;
        break;
    case LEFT:
        if (snake->position.x <= 0)
        {
            snake->position.x = GRID_DIMENSION - 2;
            return;
        }

        snake->position.x--;
        break;
    case RIGHT:
        if (snake->position.x >= GRID_DIMENSION - 2)
        {
            snake->position.x = 0;
            return;
        }

        snake->position.x++;
        break;
    }

    check_apple_collision();
    check_self_collision();

    // Moves the tail
    struct snake_element *temp = snake;

    temp = temp->next_element;
    while (temp != NULL)
    {
        save_x = temp->position.x;
        save_y = temp->position.y;

        temp->position.x = previous_x;
        temp->position.y = previous_y;

        temp = temp->next_element;

        previous_x = save_x;
        previous_y = save_y;
    }
}

void check_apple_collision(void)
{
    if (snake->position.x == apple->position.x && snake->position.y == apple->position.y)
        eat_apple();
}

void check_self_collision(void)
{
    struct snake_element *temp = snake;

    temp = temp->next_element;
    while (temp != NULL)
    {
        if (snake->position.x == temp->position.x && snake->position.y == temp->position.y)
        {
            is_game_lost = true;
            return;
        }

        temp = temp->next_element;
    }
}

void eat_apple(void)
{
    add_snake_element();
    increase_score();
    increase_game_speed();
    spawn_apple();
}

void add_snake_element(void)
{
    struct snake_element *temp = snake;
    struct snake_element *new_element = (struct snake_element *)malloc(sizeof(struct snake_element));

    while (temp->next_element != NULL)
    {
        temp = temp->next_element;
    }

    new_element->next_element = NULL;
    temp->next_element = new_element;
}

void snake_cleanup(void)
{
    struct snake_element *temp;

    while (snake != NULL)
    {
        temp = snake;
        snake = snake->next_element;
        temp->next_element = NULL;
        free(temp);
    }

    snake = NULL;
}