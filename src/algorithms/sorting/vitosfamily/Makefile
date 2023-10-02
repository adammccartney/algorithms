CC = gcc
#CFLAGS := -std=c99 -Wextra -Werror -g -O0
CFLAGS := -lm -lcrypt -O2 -pipe -ansi

all: vito

.PHONY: all clean

vito: vito.c vito.h
	$(CC) $(CFLAGS) -o vito vito.c

clean:
	rm -f vito
