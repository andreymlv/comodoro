
include config.mk

SRC = comidoro.c
OBJ = ${SRC:.c=.o}

all: options comidoro

options:
	@echo comidoro build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

${OBJ}: config.mk

clean:
	@echo cleaning
	@rm -f comidoro ${OBJ}
