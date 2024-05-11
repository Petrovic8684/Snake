#ifndef APPLE_H
#define APPLE_H

#include "../game/game.h"
#include "../util/math.h"
#include <time.h>

extern struct apple *apple;

struct apple
{
    struct vector2 position;
};

void initialize_apple(void);
void spawn_apple(void);
void apple_cleanup(void);

#endif