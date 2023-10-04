SUBDIRS := src/algorithms/sorting/vitosfamily
SUBDIRS += src/algorithms/compoundwords
SUBDIRS += src/algorithms/descdict
SUBDIRS += src/algorithms/foodlines
SUBDIRS += src/algorithms/snowflakes
SUBDIRS += src/algorithms/sorting
SUBDIRS += src/algorithms/trickrtree

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
	cp src/io/build/*.a libs
