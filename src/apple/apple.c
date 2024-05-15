#include "apple.h"

struct apple *apple = NULL;

void initialize_apple(void)
{
    apple = (struct apple *)malloc(sizeof(struct apple));
}

void spawn_apple(void)
{
    Uint8 vertical;
    Uint8 horizontal;

    do
    {
        vertical = rand() % GRID_DIMENSION;
        horizontal = rand() % (GRID_DIMENSION - 1);
    } while (grid->content[vertical][horizontal] != 0);

    apple->position.x = horizontal;
    apple->position.y = vertical;
}

void apple_cleanup(void)
{
    free(apple);
    apple = NULL;
}