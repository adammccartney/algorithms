.POSIX:
.SUFFIXES:
CC = gcc
CFLAGS = -fPIC -shared -Wall -Wextra -Werror -pedantic -std=c99 -g
PREFIX := /usr/local

libadio: libadio.so
install: libadio
	mkdir -p $(DESTDIR)$(PREFIX)/lib
	cp -f libadio.so $(DESTDIR)$(PREFIX)/lib
	cp -f adio.h $(DESTDIR)$(PREFIX)/include
libadio.so: adio.c adio.h
	$(CC) $(CFLAGS) -o libadio.so adio.c adio.h

.PHONY: clean

clean:
	rm libadio.so
