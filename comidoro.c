/* MIT License Pomidoro Timer */

#include <SDL2/SDL.h>
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

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

static void bell();
static void parse_command_line(int argc, char **argv);
static void init_sdl();
static void finalize_sdl();

// The window we'll be rendering to
static SDL_Window *window = NULL;
// The surface contained by the window
static SDL_Surface *screenSurface = NULL;
static int sections = 0;
static int section_time = 0;
static int relax_time = 0;
static int state;

static void bell() {}

static void parse_command_line(int argc, char **argv) {
  if (argc != 4) {
    fprintf(stderr, "Usage: \ncomidoro <sections> <time> <relax>\n");
    exit(1);
  } else {
    sections = strtol(argv[1], NULL, 10);
    section_time = strtol(argv[2], NULL, 10);
    relax_time = strtol(argv[3], NULL, 10);
  }
}

static void init_sdl() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  } else {
    // Create window
    window = SDL_CreateWindow("comidoro", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    } else {
      // Get window surface
      screenSurface = SDL_GetWindowSurface(window);

      // Fill the surface white
      SDL_FillRect(screenSurface, NULL,
                   SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

      // Update the surface
      SDL_UpdateWindowSurface(window);

      // Wait two seconds
      SDL_Delay(2000);
    }
  }
}

static void finalize_sdl() {
  // Destroy window
  SDL_DestroyWindow(window);
  // Quit SDL subsystems
  SDL_Quit();
}

int main(int argc, char **argv) {

  parse_command_line(argc, argv);

  printf("sections - %d\ntime - %d\nrelax - %d\n", sections, section_time,
         relax_time);

  init_sdl();
  finalize_sdl();

  return 0;
}
