.POSIX:
.SUFFIXES:
CC = gcc
CFLAGS = -fPIC -shared -Wall -Wextra -Werror -pedantic -std=c99 -g -O2
PREFIX := /usr/local

libabinarytree: libabinarytree.so
install: libabinarytree
	mkdir -p $(DESTDIR)$(PREFIX)/lib
	cp -f libabinarytree.so $(DESTDIR)$(PREFIX)/lib
	cp -f abinarytree.h $(DESTDIR)$(PREFIX)/include

libabinarytree.so: abinarytree.c abinarytree.h
	$(CC) $(CFLAGS) -o libabinarytree.so abinarytree.c abinarytree.h

.PHONY: clean distclean

clean:
	rm libabinarytree.so

distclean:
	rm -f $(DESTDIR)$(PREFIX)/lib/libanarytree.so
	rm -f $(DESTDIR)$(PREFIX)/include/abinarytree.h
