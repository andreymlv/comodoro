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

static int bell();
static int parse_command_line(int argc, char **argv);
static int load_media();
static int init_sdl();
static void finalize_sdl();
static void start(int time, char **str);

// The window we'll be rendering to
static SDL_Window *window = NULL;
// The surface contained by the window
static SDL_Surface *screenSurface = NULL;
// The music that will be played
static Mix_Music *gMusic = NULL;
static int sections = 0;
static int section_time = 0;
static int relax_time = 0;
static int state = Started;

static int bell() {
  return 0;
}

static int parse_command_line(int argc, char **argv) {

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
  int success = 0;

  // Load music
  gMusic = Mix_LoadMUS("bell.wav");
  if (gMusic == NULL) {
    printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
    success = -1;
  }

  return success;
}

static int init_sdl() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return -1;
  }

  // Create window
  window = SDL_CreateWindow("comidoro", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return -1;
  }
  // Get window surface
  screenSurface = SDL_GetWindowSurface(window);

  // Fill the surface white
  SDL_FillRect(screenSurface, NULL,
               SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

  // Update the surface
  SDL_UpdateWindowSurface(window);

  // Wait two seconds
  SDL_Delay(2000);

  return 0;
}

static void finalize_sdl() {
  // Free the music
  Mix_FreeMusic(gMusic);
  gMusic = NULL;

  // Destroy window
  SDL_DestroyWindow(window);
  // Quit SDL subsystems
  Mix_Quit();
  SDL_Quit();
}

int main(int argc, char **argv) {

  parse_command_line(argc, argv);

  printf("sections - %d\ntime - %d\nrelax - %d\n", sections, section_time,
         relax_time);
  
  if (init_sdl()) {
    if (load_media()) {
      int current_section = 0;
      while (++current_section < sections) {
//        start(section_time, "End of section! Relax time!");
//        start(relax_time, "End of relax! Section time!");
      }
    }
  }

  finalize_sdl();

  return 0;
}
