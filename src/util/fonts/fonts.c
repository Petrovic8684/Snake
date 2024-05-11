#include "fonts.h"

TTF_Font *font = NULL;

struct text score_text;
struct text paused_text;

struct text snake_text;
struct text made_by_text;
struct text press_enter_to_start_text;

bool has_game_text_changed = true;
bool should_render_snake_text = true;

void initialize_text(void)
{
    if (TTF_Init() == -1)
    {
        fprintf(stderr, "SDL_ttf failed to initialize: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    font = TTF_OpenFont("assets/fonts/runescape.ttf", 36);
}

void update_text(const char *prefix, bool has_variable, const int variable, SDL_Color color, int x, int y, bool add_padding, struct text *text)
{
    if (has_variable == true)
    {
        char string[20];
        string[0] = '\0';
        if (add_padding == true)
            sprintf(string, "%s %06d", prefix, variable);
        else
            sprintf(string, "%s %d", prefix, variable);

        text->text_surface = TTF_RenderText_Solid(font, string, color);
    }
    else
    {
        text->text_surface = TTF_RenderText_Solid(font, prefix, color);
    }

    text->text_texture = SDL_CreateTextureFromSurface(renderer, text->text_surface);

    text->text_rect.x = x;
    text->text_rect.y = y;
    text->text_rect.w = text->text_surface->w;
    text->text_rect.h = text->text_surface->h;
}

void render_game_text(void)
{
    if (has_game_text_changed == true)
    {
        update_text("Score: ", true, score, color_green, 20, 650, true, &score_text);

        if (is_paused == true)
            update_text("PAUSED", false, -1, color_white, 480, 650, false, &paused_text);
        else
            update_text(" ", false, -1, color_white, 480, 650, false, &paused_text);

        has_game_text_changed = false;
    }

    SDL_RenderCopy(renderer, score_text.text_texture, NULL, &score_text.text_rect);
    SDL_RenderCopy(renderer, paused_text.text_texture, NULL, &paused_text.text_rect);
}

void render_snake_text(void)
{
    if (should_render_snake_text == true)
    {
        TTF_SetFontSize(font, 70);
        update_text(" S  N  A  K  E", false, -1, get_random_color(), WINDOW_WIDTH / 4 + 2, WINDOW_HEIGHT / 4 + 30, false, &snake_text);

        should_render_snake_text = false;
    }
}

void render_menu_text(void)
{
    TTF_SetFontSize(font, 36);
    update_text("Made by Jovan Petrovic", false, -1, color_white, WINDOW_WIDTH / 5 + 25, WINDOW_HEIGHT / 3 + 75, false, &made_by_text);
    update_text("Press ENTER to start", false, -1, color_white, WINDOW_WIDTH / 5 + 40, WINDOW_HEIGHT / 3 + 125, false, &press_enter_to_start_text);

    SDL_RenderCopy(renderer, snake_text.text_texture, NULL, &snake_text.text_rect);
    SDL_RenderCopy(renderer, made_by_text.text_texture, NULL, &made_by_text.text_rect);
    SDL_RenderCopy(renderer, press_enter_to_start_text.text_texture, NULL, &press_enter_to_start_text.text_rect);
};

void text_cleanup(struct text *text)
{
    SDL_FreeSurface(text->text_surface);
    SDL_DestroyTexture(text->text_texture);

    text->text_surface = NULL;
    text->text_texture = NULL;
}

void font_cleanup(void)
{
    TTF_CloseFont(font);
    font = NULL;

    TTF_Quit();
}