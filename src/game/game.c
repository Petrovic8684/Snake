#include "game.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool is_window_open = true;
bool is_paused = false;
bool is_in_menu = true;
bool is_game_lost = false;

int score = 0;
int game_speed = STARTING_GAME_SPEED;

enum grid_style grid_style = GRID_ON;

void initialize_sdl(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "SDL failed to initialize: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void create_window_and_renderer(const char *title)
{
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    if (window == NULL)
    {
        fprintf(stderr, "SDL window failed to initialize: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if (renderer == NULL)
    {
        fprintf(stderr, "SDL renderer failed to initialize: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void handle_input(SDL_Event event)
{
    switch (event.key.keysym.sym)
    {
    case SDLK_RETURN:
        if (is_in_menu == false)
            return;
        is_in_menu = false;
        break;
    case SDLK_ESCAPE:
        if (is_in_menu == true)
            return;
        if (is_paused == true)
            is_paused = false;

        is_in_menu = true;
    case SDLK_p:
        if (is_in_menu == true)
            return;
        is_paused = !is_paused;
        has_game_text_changed = true;
        break;
    case SDLK_LEFT:
        if (is_in_menu == true || is_paused == true)
            return;
        change_snake_direction(LEFT);
        break;
    case SDLK_RIGHT:
        if (is_in_menu == true || is_paused == true)
            return;
        change_snake_direction(RIGHT);
        break;
    case SDLK_DOWN:
        if (is_in_menu == true || is_paused == true)
            return;
        change_snake_direction(DOWN);
        break;
    case SDLK_UP:
        if (is_in_menu == true || is_paused == true)
            return;
        change_snake_direction(UP);
        break;
    case SDLK_g:
        if (is_in_menu == true || is_paused == true)
            return;
        grid_style = (grid_style + 1) % 3;
        break;
    }
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

void render(void)
{
    SDL_SetRenderDrawColor(renderer, color_black.r, color_black.g, color_black.b, 255);
    SDL_RenderClear(renderer);

    render_grid();
    render_game_text();

    SDL_RenderPresent(renderer);
}

void initialize_game(void)
{
    score = 0;
    has_game_text_changed = true;

    game_speed = STARTING_GAME_SPEED;

    initialize_snake();
    initialize_grid();
}

void increase_game_speed(void)
{
    game_speed += 100;
}

void increase_score(void)
{
    score++;
    has_game_text_changed = true;
}

void restart_game(void)
{
    is_game_lost = false;

    grid_cleanup();
    initialize_game();
}

void start_game_and_keep_running(void)
{
    Uint32 start_time = SDL_GetTicks();
    Uint32 end_time, elapsed_time;

menu:
    restart_game();
    while (is_window_open == true && is_in_menu == true)
    {
        SDL_SetRenderDrawColor(renderer, color_black.r, color_black.g, color_black.b, 255);
        SDL_RenderClear(renderer);

        end_time = SDL_GetTicks();
        elapsed_time = end_time - start_time;

        if (elapsed_time > 1500)
        {
            start_time = end_time;
            should_render_snake_text = true;
        }

        render_snake_text();
        render_menu_text();

        poll_events();
        SDL_RenderPresent(renderer);
    }

    start_time = SDL_GetTicks();

game:
    while (is_window_open == true && is_game_lost == false)
    {
        render();
        poll_events();

        if (is_in_menu == true)
            goto menu;

        if (is_paused == false)
        {
            end_time = SDL_GetTicks();
            elapsed_time = end_time - start_time;

            if (elapsed_time > game_speed)
            {
                start_time = end_time;
                move_snake();
            }

            update_grid();
        }
    }

    if (is_game_lost)
    {
        restart_game();
        goto game;
    }
}

void game_cleanup(void)
{
    text_cleanup(&score_text);
    text_cleanup(&paused_text);
    text_cleanup(&snake_text);
    text_cleanup(&made_by_text);
    text_cleanup(&press_enter_to_start_text);

    font_cleanup();
    sound_cleanup();

    grid_cleanup();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}