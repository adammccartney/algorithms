CC := gcc
CFLAGS := -g -O0 -Wall -std=c11

EXECUTABLES := snowflakes hashtable 

all: $(EXECUTABLES)

snowflakes: snowflakes.c 
	$(CC) $(CFLAGS) -o $@ $<

hashtable: hashtable.c 
	$(CC) $(CFLAGS) -o $@ $<

.PHONY:
clean:
	rm $(EXECUTABLES) 
