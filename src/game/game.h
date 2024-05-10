#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "../grid/grid.h"
#include "../util/sounds/sounds.h"

#define WINDOW_DIMENSION 600

extern SDL_Window *window;
extern SDL_Renderer *renderer;

extern bool is_window_open;

void initialize_sdl(void);
void create_window_and_renderer(const char *title);
void handle_input(SDL_Event event);
void poll_events(void);
void initialize_game(void);
void render(void);
void start_game_and_keep_running(void);
void game_cleanup(void);

#endif