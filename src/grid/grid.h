#ifndef GRID_H
#define GRID_H

#include <SDL2/SDL.h>

#define GRID_DIMENSION 20

struct grid
{
    Uint8 content[GRID_DIMENSION][GRID_DIMENSION];
    SDL_Color color[GRID_DIMENSION][GRID_DIMENSION];
};

extern struct grid *grid;

void initialize_grid(void);
void render_grid(SDL_Renderer *renderer, const int window_dimension);
void grid_cleanup(void);

#endif