.POSIX:
.SUFFIXES:
CC = gcc
CFLAGS := -std=c99 -Wall -Werror -Wextra -Werror -Wno-unused-function -O0 -g
LDFLAGS :=
LDLIBS :=
PREFIX := /usr/local

EXE := bicoloring
all: $(EXE)


.PHONY: all clean

bicoloring: bicoloring.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

bicoloring.o: bicoloring.c bicoloring.h
	$(CC) -c $(CFLAGS) $<

clean:
	rm -rf *.o $(EXE)
