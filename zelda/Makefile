# Simple Makefile for Zelda terminal game

CC := gcc
CFLAGS := -D_POSIX_C_SOURCE=200809L -std=c11 -Wall -Wextra -pedantic -Os
LDFLAGS := -lncurses -lm -s

SRC := main.c game.c render.c
OBJ := $(SRC:.c=.o)
BIN := zelda_game

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean run

run: $(BIN)
	./$(BIN)

clean:
	rm -f $(OBJ) $(BIN)
