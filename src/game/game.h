#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "../grid/grid.h"
#include "../snake/snake.h"
#include "../util/colors/colors.h"
#include "../util/sounds/sounds.h"
#include "../util/fonts/fonts.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 700

#define STARTING_GAME_SPEED 1000;

extern SDL_Window *window;
extern SDL_Renderer *renderer;

extern bool is_window_open;
extern bool is_paused;
extern bool is_in_menu;
extern bool is_game_lost;
extern int game_speed;

extern int score;
extern enum grid_style grid_style;

void initialize_sdl(void);
void create_window_and_renderer(const char *title);
void handle_input(SDL_Event event);
void poll_events(void);
void render(void);
void initialize_game(void);
void increase_game_speed(void);
void increase_score(void);
void restart_game(void);
void start_game_and_keep_running(void);
void game_cleanup(void);

#endif