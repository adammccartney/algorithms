CC = gcc
CFLAGS := -std=c99 -Wall -Werror -g -O0

all: vito

.PHONY: all clean

vito: vito.c vito.h
	$(CC) $(CFLAGS) -o vito vito.c

clean:
	rm -f vito
