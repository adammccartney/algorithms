CC := gcc
CFLAGS := -Wall -g -O0

.PHONY: clean all

all: compoundwords

compoundwords: compoundwords.c 
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm compoundwords
