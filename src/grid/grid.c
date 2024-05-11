#include "grid.h"

struct grid *grid = NULL;

void initialize_grid(void)
{
    grid = (struct grid *)malloc(sizeof(struct grid));
    memset(grid->content, 0, sizeof(Uint8[GRID_DIMENSION][GRID_DIMENSION]));
}

void render_grid()
{
    SDL_Rect cell;
    cell.w = cell.h = GRID_DIMENSION;

    SDL_Rect rect;
    rect.w = rect.h = GRID_DIMENSION;

    for (Uint8 i = 0; i < GRID_DIMENSION; i++)
        for (Uint8 j = 0; j < GRID_DIMENSION; j++)
        {
            if (grid_style == GRID_ON)
            {
                SDL_SetRenderDrawColor(renderer, color_gray.r, color_gray.g, color_gray.b, 255);

                cell.x = j * GRID_DIMENSION;
                cell.y = i * GRID_DIMENSION;
                SDL_RenderDrawRect(renderer, &cell);
            }

            if (grid->content[i][j] == 1 || grid->content[i][j] == 2)
            {
                rect.x = j * GRID_DIMENSION;
                rect.y = i * GRID_DIMENSION;
                SDL_SetRenderDrawColor(renderer, grid->color[i][j].r, grid->color[i][j].g, grid->color[i][j].b, 255);
                SDL_RenderFillRect(renderer, &rect);

                if (grid_style == GRID_ON || grid_style == GRID_ONLY_SNAKE)
                {
                    SDL_SetRenderDrawColor(renderer, color_gray.r, color_gray.g, color_gray.b, 255);
                    SDL_RenderDrawRect(renderer, &rect);
                }
            }
        }
}

void update_grid(void)
{
    for (Uint8 i = 0; i < GRID_DIMENSION; i++)
        for (Uint8 j = 0; j < GRID_DIMENSION; j++)
        {
            if (snake->position.x == j && snake->position.y == i)
            {
                grid->content[i][j] = 1;
                grid->color[i][j] = color_green;
            }
            else if (apple->position.x == j && apple->position.y == i)
            {
                grid->content[i][j] = 2;
                grid->color[i][j] = color_red;
            }
            else
            {
                grid->content[i][j] = 0;
                grid->color[i][j] = color_gray;
            }
        }
}

/*void print_grid(void)
{
    for (Uint8 i = 0; i < GRID_DIMENSION; i++)
    {
        for (Uint8 j = 0; j < GRID_DIMENSION; j++)
        {
            fprintf(stdout, "%d ", grid->content[i][j]);
        }

        fprintf(stdout, "\n");
    }

    fprintf(stdout, "\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "\n");
}*/

void grid_cleanup(void)
{
    free(grid);
    grid = NULL;
}