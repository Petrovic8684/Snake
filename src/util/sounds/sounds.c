#include "sounds.h"

Mix_Music *music_sound = NULL;
Mix_Chunk *eat_sound = NULL;

void initialize_sound(void)
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        fprintf(stderr, "SDL_mixer failed to initialize: %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
    }

    load_sounds();
    play_music();
}

void load_sounds(void)
{
    music_sound = Mix_LoadMUS("assets/sounds/music.mp3");

    if (music_sound == NULL)
    {
        fprintf(stderr, "Music failed to load: %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
    }

    eat_sound = Mix_LoadWAV("assets/sounds/eat.wav");
    if (eat_sound == NULL)
    {
        fprintf(stderr, "Eat sound failed to load: %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
    }
}

void play_music(void)
{
    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(music_sound, -1);
    }
}

void play_eat_sound(void)
{
    Mix_PlayChannel(-1, eat_sound, 0);
}

void sound_cleanup(void)
{
    Mix_FreeMusic(music_sound);
    Mix_FreeChunk(eat_sound);

    music_sound = NULL;
    eat_sound = NULL;

    Mix_Quit();
}