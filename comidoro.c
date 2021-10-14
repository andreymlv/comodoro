/* MIT License Pomidoro Timer */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ESC 27 /* For beep function */

enum {
  Started,
  Stopped,
  Paused,
  Relaxed,
  Beeped,
  LastState,
};

static void *beep(void *values);
static void parse_command_line(int argc, char **argv);

static int sections = 0;
static int section_time = 0;
static int relax_time = 0;
static int state;

static void *beep(void *time_to_sleep) {
  FILE *tty;

  if (NULL == (tty = fopen("/dev/console", "w"))) {
    fprintf(stderr, "Cannot write to /dev/console!\n");
    exit(1);
  }

  int *delay = (int *)time_to_sleep;

  int frequency = 512;
  int duration = 512;

  fprintf(tty, "%c[10;%d]%c[11;%d]\a", ESC, frequency, ESC, duration);
  printf("Beep! Delay: %d\n", *delay);
  sleep(*delay);

  return NULL;
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

  for (int i = 0; i < sections; ++i) {
    pthread_t threads;
    sleep(1);
    pthread_create(&threads, NULL, &beep, &i);
    pthread_join(&threads, NULL);
  }

  return 0;
}
