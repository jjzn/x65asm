SRC = $(wildcard src/*.c) $(GEN)
OBJ = $(SRC:.c=.o)
GEN = src/emit.c

CFLAGS = -Wall -Wextra -Wpedantic -Wconversion -Wdouble-promotion -std=c11 -fsanitize=address,undefined
LDFLAGS = -fsanitize=address,undefined
PREFIX = ~/.local/bin/

.PHONY = all clean remake debug install uninstall

all: x65asm

x65asm: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(GEN): %.c: %.c.in
	m4 $^ > $@

$(OBJ): %.o: %.c
	$(CC) -c -o $@ $^ $(CFLAGS)

clean:
	rm -f x65asm src/*.o $(GEN)

remake: clean all

debug: CFLAGS += -g3 -DDEBUG
debug: remake

install: all
	install x65asm $(PREFIX)
uninstall:
	rm -f $(PREFIX)/x65asm
