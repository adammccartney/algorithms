CC := gcc
CFLAGS := -Wall -g -O2

EXE := descdist

descdist: descdist.c 
	$(CC) $(CFLAGS) -o $@ $<

.PHONY:
clean:
	rm -rf $(EXE) 
