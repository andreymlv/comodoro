/* MIT License Pomidoro Timer */

#include <stdio.h>
#include <stdlib.h>

#define NUM_OF_STATES 2

enum {
    Stopped,
    Paused,
};

static int beep();

static int sections = 0;
static int time = 0;
static int relax = 0;
static int state[NUM_OF_STATES];

static int beep() {
    return 0;
}

int main(int argc, char **argv) {


    if (argc != 4) {
        printf("Usage: \ncomidoro <sections> <time> <relax>\n");
        return -1;
    } else {
        sections = strtol(argv[1], NULL, 10); 
        time = strtol(argv[2], NULL, 10); 
        relax = strtol(argv[3], NULL, 10); 
    }

    printf("sections - %d\ntime - %d\nrelax - %d\n", sections, time, relax);

    return 0;
}

