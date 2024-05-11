#ifndef SNAKE_H
#define SNAKE_H

#include "../game/game.h"

struct vector2
{
    Uint8 x;
    Uint8 y;
};

struct snake_element
{
    struct vector2 position;
    struct snake_element *next_element;
};

enum movement_direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

extern struct snake_element *snake;
extern enum movement_direction target_direction;

void initialize_snake(void);
void change_snake_direction(enum movement_direction direction);
void move_snake(void);

#endif