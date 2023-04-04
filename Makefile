SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c11

.PHONY = all clean remake debug install

all: x65asm

x65asm: $(OBJ)
	$(CC) -o $@ $^

$(OBJ): %.o: %.c
	$(CC) -c -o $@ $^ $(CFLAGS)

clean:
	rm -f x65asm src/*.o

remake: clean all

debug: CFLAGS += -g -DDEBUG
debug: remake

install: all
	install x86asm ~/.local/bin/
