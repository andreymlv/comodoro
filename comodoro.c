/*
 * MIT License
 * Pomidoro Timer in C language using SDL2 library
 */

/* System headers */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* SDL2 headers */
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#define CURRENT_TIME (SDL_GetTicks() / 1000)

typedef enum {
    Sleeping,
    Playing,
    Resumed,
    Paused,
    Halted,
    Stopped,
    Section,
    Relax,
    WaitSection,
    WaitRelax
} States;

static int parse_command_line(int argc, const char *argv[]);
static int load_media();
static void play_or_pause_music();
static void halt_music();
static void render();
static void poll_events();
static void main_loop();
static int make_window();
static int init_sdl();
static void finalize_sdl();

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

static int quit = 0;
static SDL_Window *window = NULL;
static SDL_Surface *screenSurface = NULL;
static SDL_Event e;
static Mix_Music *gMusic = NULL;
static int sections = 0;
static int current_section = 0;
static unsigned int section_time = 0;
static unsigned int relax_time = 0;
static unsigned int current_time = 0;
static int state = Sleeping;

static int parse_command_line(int argc, const char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: \ncomodoro <sections> <time> <relax>\n");
        return -1;
    }

    sections = strtol(argv[1], NULL, 10);
    section_time = strtol(argv[2], NULL, 10) * 60;
    relax_time = strtol(argv[3], NULL, 10) * 60;

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

static void play_or_pause_music() {
    if (Mix_PlayingMusic() == 0) {
        state = Playing;
        printf("Play\n");
        Mix_PlayMusic(gMusic, -1);
    } else if (Mix_PausedMusic() == 1) {
        state = Resumed;
        printf("Resume\n");
        Mix_ResumeMusic();
    } else {
        state = Paused;
        printf("Pause\n");
        Mix_PauseMusic();
    }
}

static void halt_music() {
    state = Halted;
    printf("Halt\n");
    Mix_HaltMusic();
}

static void render() {
    SDL_FillRect(screenSurface, NULL,
                 SDL_MapRGB(screenSurface->format, 0x3E, 0xB4, 0x89));
    SDL_UpdateWindowSurface(window);
}

static void poll_events() {
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT)
            quit = 1;
        else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_1:
                    printf("1 - ");
                    play_or_pause_music();
                    state = Sleeping;
                    break;
                case SDLK_2:
                    printf("2 - ");
                    halt_music();
                    state = Sleeping;
                    break;
                case SDLK_3:
                    printf("3 - ");
                    if (state == WaitSection || state == Sleeping) {
                        printf("Section started\n");
                        state = Section;
                    } else if (state == WaitRelax) {
                        printf("Relax started\n");
                        state = Relax;
                    }
                    break;
                case SDLK_ESCAPE:
                    printf("Escape - Stop\n");
                    state = Stopped;
                    quit = 1;
                    break;
                default:
                    break;
            }
        }
    }
}

static void main_loop() {
    while (!quit) {
        render();

        switch (state) {
            case Section:
                printf("Section state\n");
                if (current_section < sections) {
                    current_time = CURRENT_TIME;
                    while (CURRENT_TIME < current_time + section_time &&
                           !quit) {
                        sleep(1);
                        printf("section %d: %d of %d\n", current_section + 1,
                               CURRENT_TIME, current_time + section_time);
                        poll_events();
                    }
                    ++current_section;
                    state = WaitRelax;
                } else {
                    state = Sleeping;
                    printf("No other sections!\n");
                }
                break;
            case Relax:
                if (current_section < sections) {
                    printf("Relax state\n");
                    current_time = CURRENT_TIME;
                    while (CURRENT_TIME < current_time + relax_time && !quit) {
                        sleep(1);
                        printf("relax: %d of %d\n", CURRENT_TIME,
                               current_time + relax_time);
                        poll_events();
                    }
                    state = WaitSection;
                } else {
                    state = Sleeping;
                    printf("No other sections!\n");
                }
                break;
            case WaitSection:
                play_or_pause_music();
                break;
            case WaitRelax:
                play_or_pause_music();
                break;
            default:
                break;
        }

        if (current_time < CURRENT_TIME) printf("%d\n", current_time);

        current_time = CURRENT_TIME;

        poll_events();
    }
}

static int make_window() {
    window = SDL_CreateWindow("comodoro", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_VULKAN);
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

int main(int argc, const char *argv[]) {
    if (parse_command_line(argc, argv)) {
        printf("Arguments Error!\n");
        return -1;
    }

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
