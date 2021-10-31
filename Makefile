
include config.mk

SRC = comidoro.c
OBJ = ${SRC:.c=.o}

all: options comidoro

options:
	@echo comidoro build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC      = ${CC}"

ccls: clean
	intercept-build make all

${OBJ}: config.mk

clean:
	@echo cleaning
	@rm -f comidoro ${OBJ}
	@rm -f compile_commands.json 

run: all
	./comidoro 3 3 3

check: ccls
	cppcheck --clang --std=c17 .
