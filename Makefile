
include config.mk

SRC = comodoro.c
OBJ = ${SRC:.c=.o}

all: options comodoro

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
	./comodoro 3 1 1

check: ccls
	cppcheck --clang --std=c17 .
