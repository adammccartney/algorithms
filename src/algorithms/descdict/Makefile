CC := gcc
CFLAGS := -Wall -g -O2

EXE := descdist

.PHONY: all clean 

all: $(EXE)

descdist: descdist.c 
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(EXE) 
