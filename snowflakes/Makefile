CC := gcc
CFLAGS := -g -O0 -Wall -std=c11

all: snowflakes hashtable 

snowflakes: snowflakes.c 
	$(CC) $(CFLAGS) -o $@ $<

hashtable: hashtable.c 
	$(CC) $(CFLAGS) -o $@ $<

.PHONY:
clean:
	rm all
