#include "game/game.h"

int main(int argc, char const *argv[])
{
    initialize_sdl();
    create_window_and_renderer("Snake");

    initialise_game_elements();
    start_game_and_keep_running();

    cleanup();
    return EXIT_SUCCESS;
}
