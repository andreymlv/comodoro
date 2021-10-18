# comidoro version
VERSION = 0.1

# SDL2
SDL2INCS = -I/usr/include/SDL2 
SDL2LIBS = -pthread -lSDL2 -lSDL2_mixer

# Wayland
WAYLANDLIB = -lwayland-client

# includes and libs
INCS = -I${SDL2INCS}
LIBS = ${SDL2LIBS} ${WAYLANDLIB}

# flags
CPPFLAGS = -D_REENTRANT -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=200809L -DVERSION=\"${VERSION}\"
#CFLAGS   = -g -std=c99 -pedantic -Wall -Wextra -O0 ${INCS} ${CPPFLAGS}
CFLAGS   = -std=c99 -pedantic -Wall -Wno-deprecated-declarations -O3  ${CPPFLAGS}
LDFLAGS  = ${LIBS}

# compiler and linker
CC = cc
