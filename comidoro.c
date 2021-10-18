/* MIT License Pomidoro Timer */

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    Started,
    Stopped,
    Paused,
    Relaxed,
    Beeped,
    LastState,
};

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

static int parse_command_line(int argc, const char **argv);
static int load_media();
static void poll_events();
static void main_loop();
static int make_window();
static int init_sdl();
static void finalize_sdl();

static int quit = 0;
static SDL_Window *window = NULL;
static SDL_Surface *screenSurface = NULL;
static SDL_Event e;
static Mix_Music *gMusic = NULL;
static int sections = 0;
static int section_time = 0;
static int relax_time = 0;
static int state = Started;

static int parse_command_line(int argc, const char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: \ncomidoro <sections> <time> <relax>\n");
        return -1;
    }

    sections = strtol(argv[1], NULL, 10);
    section_time = strtol(argv[2], NULL, 10);
    relax_time = strtol(argv[3], NULL, 10);

    return 0;
}

static int load_media() {
    gMusic = Mix_LoadMUS("bell.wav");
    if (gMusic == NULL) {
        printf("Failed to load beat music! SDL_mixer Error: %s\n",
               Mix_GetError());
        return -1;
    }

    return 0;
}

static void poll_events() {
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT)
            quit = 1;
        else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_1:
                    printf("1 - ");
                    if (Mix_PlayingMusic() == 0) {
                        printf("Play\n");
                        Mix_PlayMusic(gMusic, -1);
                    } else if (Mix_PausedMusic() == 1) {
                        printf("Resume\n");
                        Mix_ResumeMusic();
                    } else {
                        printf("Pause\n");
                        Mix_PauseMusic();
                    }
                    break;
                case SDLK_2:
                    printf("2 - Halt\n");
                    Mix_HaltMusic();
                    break;
                default:
                    break;
            }
        }
    }
}

static void main_loop() {
    while (!quit) {
        poll_events();

        SDL_FillRect(screenSurface, NULL,
                     SDL_MapRGB(screenSurface->format, 0xBF, 0xCF, 0xAF));
        SDL_UpdateWindowSurface(window);
    }
}

static int make_window() {
    window = SDL_CreateWindow("comidoro", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    screenSurface = SDL_GetWindowSurface(window);

    return 0;
}

static int init_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n",
               Mix_GetError());
        return -1;
    }

    if (load_media()) {
        printf("Load Media Error!\n");
        return -1;
    }

    return 0;
}

static void finalize_sdl() {
    Mix_FreeMusic(gMusic);
    gMusic = NULL;

    SDL_DestroyWindow(window);

    Mix_Quit();
    SDL_Quit();
}

int main(int argc, const char **argv) {
    parse_command_line(argc, argv);

    printf("sections - %d\ntime - %d\nrelax - %d\n", sections, section_time,
           relax_time);

    if (init_sdl()) {
        printf("SDL Init Error!\n");
        return -1;
    }

    if (make_window()) {
        printf("Window Create Error!\n");
        return -1;
    }

    main_loop();

    finalize_sdl();

    return 0;
}
