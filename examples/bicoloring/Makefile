.POSIX:
.SUFFIXES:
CC = gcc
CFLAGS := -std=c99 -Wall -Werror -Wextra -Werror -Wno-unused-function -O0 -g
LDFLAGS := -L${HOME}/.local/lib
LDLIBS := -ladio
PREFIX := /usr/local

EXE := bicoloring
all: $(EXE)


.PHONY: all clean

bicoloring: bicoloring.o ad_graph.o ad_queue.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

bicoloring.o: bicoloring.c bicoloring.h
	$(CC) -c $(CFLAGS) $<

ad_queue.o: ad_queue.c ad_queue.h
	$(CC) -c $(CFLAGS) $<

ad_graph.o: ad_graph.c ad_graph.h
	$(CC) -c $(CFLAGS) $<



clean:
	rm -rf *.o $(EXE)
