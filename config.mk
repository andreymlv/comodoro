# comidoro version
VERSION = 0.1

#X11INC = /usr/X11R6/include
#X11LIB = /usr/X11R6/lib

# Xinerama, comment if you don't want it
#XINERAMALIBS  = -lXinerama
#XINERAMAFLAGS = -DXINERAMA

# freetype
#FREETYPELIBS = -lfontconfig -lXft
#FREETYPEINC = /usr/include/freetype2

# includes and libs
#INCS = -I${X11INC} -I${FREETYPEINC}
LIBS = -lpthread

# flags
CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=200809L -DVERSION=\"${VERSION}\"
CFLAGS   = -g -std=c99 -pedantic -Wall -O0 ${INCS} ${CPPFLAGS}
#CFLAGS   = -std=c99 -pedantic -Wall -Wno-deprecated-declarations -Os  ${CPPFLAGS}
LDFLAGS  = ${LIBS}

# compiler and linker
CC = gcc
