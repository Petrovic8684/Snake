#include "grid.h"

struct grid *grid = NULL;

void initialize_grid(void)
{
    grid = (struct grid *)malloc(sizeof(struct grid));
    memset(grid->content, 0, sizeof(Uint8[GRID_DIMENSION][GRID_DIMENSION]));
}

void render_grid()
{
    int tile_size = WINDOW_DIMENSION / GRID_DIMENSION;

    SDL_Rect cell;
    cell.w = cell.h = tile_size;

    SDL_Rect rect;
    rect.w = rect.h = tile_size;

    for (Uint8 i = 0; i < GRID_DIMENSION; i++)
        for (Uint8 j = 0; j < GRID_DIMENSION; j++)
        {
            SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);

            cell.x = j * tile_size;
            cell.y = i * tile_size;
            SDL_RenderDrawRect(renderer, &cell);

            if (grid->content[i][j] == 1)
            {
                rect.x = j * tile_size;
                rect.y = i * tile_size;
                SDL_SetRenderDrawColor(renderer, grid->color[i][j].r, grid->color[i][j].g, grid->color[i][j].b, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
}

void grid_cleanup(void)
{
    free(grid);
    grid = NULL;
}