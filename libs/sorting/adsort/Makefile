CC := gcc 
CFLAGS := -std=c99 -Wall -Werror -g -O0

all: adsort

.PHONY: all clean

adsort: adsort.c adsort.h
	$(CC) $(CFLAGS) -o adsort adsort.c

clean:
	rm -rf adsort
