
<<<<<<< HEAD
SUBDIRS := src/algorithms/sorting/vitosfamily
=======
SUBDIRS := src/algorithms/sorting/vitosfamily 
>>>>>>> d12baf0 (Restructure)
SUBDIRS += src/algorithms/compoundwords
SUBDIRS += src/algorithms/descdict
SUBDIRS += src/algorithms/foodlines
SUBDIRS += src/algorithms/snowflakes
SUBDIRS += src/algorithms/sorting
SUBDIRS += src/algorithms/trickrtree

<<<<<<< HEAD
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
=======
.PHONY: clean all 

all clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir $@; \
	done
>>>>>>> d12baf0 (Restructure)
