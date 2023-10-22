.POSIX:
.SUFFIXES:
CC = gcc
CFLAGS := -fPIC -shared -std=c99 -g -fPIC -Wall -Wextra -Werror -pedantic
PREFIX := /usr/local

libad: libad.so
install: libad
	mkdir -p $(DESTDIR)$(PREFIX)/lib
	cp -f libad.so $(DESTDIR)$(PREFIX)/lib
	cp -f ad.h $(DESTDIR)$(PREFIX)/include
libad.so: ad.c ad.h
	$(CC) $(CFLAGS) -o libad.so ad.c ad.h

clean:
	rm libad.so
