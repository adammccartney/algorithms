SHELL := /usr/bin/sh

CC := gcc
CFLAGS := -std=c99 -g3 -Wall -Wextra -Werror -Wno-unused-functions
LDLIBS := -lad
LDFLAGS :=

all: main

main: main.c
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

.PHONY: all clean
clean:
	rm main
