CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -O2

# Essaie d'utiliser pkg-config pour ncursesw, sinon retombe sur ncurses
NCURSES_LIBS := $(shell pkg-config --libs ncursesw 2>/dev/null || pkg-config --libs ncurses 2>/dev/null || echo -lncurses)

SRC := main.c snake.c render.c
OBJ := $(SRC:.c=.o)
BIN := snake_game

.PHONY: all clean run

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) $(NCURSES_LIBS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(BIN)

clean:
	rm -f $(OBJ) $(BIN)

