SUBDIRS := examples/vitosfamily
SUBDIRS += examples/compoundwords
SUBDIRS += examples/descdict
SUBDIRS += examples/foodlines
SUBDIRS += examples/snowflakes
SUBDIRS += examples/sorting
SUBDIRS += examples/trickrtree

.PHONY: clean all libs

all: libs

clean: clean

all:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir all; \
	done

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	rm -rf libs

libs:
	mkdir -p libs
	cp libs/io/build/*.a libs
