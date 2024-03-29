#include "game.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool is_window_open = true;

void initialize_sdl(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void create_window_and_renderer(const char *title)
{
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_DIMENSION, WINDOW_DIMENSION, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    if (window == NULL)
    {
        fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if (renderer == NULL)
    {
        fprintf(stderr, "SDL renderer failed to initialise: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void handle_input(SDL_Event event)
{
}

void poll_events(void)
{
    SDL_Event event;
    while (SDL_PollEvent(&event) > 0)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            is_window_open = false;
            break;
        case SDL_KEYUP:
            handle_input(event);
            break;
        }
    }
}

void initialise_game_elements(void)
{
    initialize_grid();
}

void start_game_and_keep_running(void)
{
    while (is_window_open == true)
    {
        SDL_SetRenderDrawColor(renderer, 12, 12, 12, 255);
        SDL_RenderClear(renderer);

        render_grid(renderer, WINDOW_DIMENSION);

        SDL_RenderPresent(renderer);

        poll_events();
    }
}

void cleanup(void)
{
    grid_cleanup();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}