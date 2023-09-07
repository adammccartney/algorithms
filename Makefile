
SUBDIRS := src/algorithms/sorting/vitosfamily 
SUBDIRS += src/algorithms/compoundwords
SUBDIRS += src/algorithms/descdict
SUBDIRS += src/algorithms/foodlines
SUBDIRS += src/algorithms/snowflakes
SUBDIRS += src/algorithms/sorting
SUBDIRS += src/algorithms/trickrtree

.PHONY: clean all 

all clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir $@; \
	done
