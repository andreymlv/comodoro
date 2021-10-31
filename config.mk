# comidoro version
VERSION = 0.1

# SDL2
SDL2INCS = /usr/include/SDL2 
SDL2LIBS = -pthread -lSDL2 -lSDL2_mixer

# includes and libs
INCS = -I${SDL2INCS}
LIBS = ${SDL2LIBS}

# flags
CPPFLAGS = -D_REENTRANT -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=200809L -DVERSION=\"${VERSION}\"
#CFLAGS   = -g -std=c17 -pedantic -Wall -Wextra -O0 ${INCS} ${CPPFLAGS}
CFLAGS   = -std=c17 -pedantic -Wall -Wno-deprecated-declarations -O2  ${CPPFLAGS}
LDFLAGS  = ${LIBS}

# compiler and linker
CC = cc
