/* MIT License Pomidoro Timer */

#include <stdio.h>
#include <stdlib.h>

#define ESC 27
#define NUM_OF_STATES 2

enum {
  Stopped,
  Paused,
};

static void beep();
static void parse_command_line(int argc, char **argv);

static int sections = 0;
static int section_time = 0;
static int relax_time = 0;
static int state[NUM_OF_STATES];

static void beep(int frequency, int duration) {
  FILE *tty;
  if (NULL == (tty = fopen("/dev/console", "w"))) {
    fprintf(stderr, "Cannot write to /dev/console!\n");
    exit(1);
  }
  fprintf(tty, "%c[10;%d]%c[11;%d]\a", ESC, frequency, ESC, duration);
}

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

int main(int argc, char **argv) {

  parse_command_line(argc, argv);
  
  printf("sections - %d\ntime - %d\nrelax - %d\n", sections, section_time,
         relax_time);

  beep(512, 1024);

  return 0;
}
