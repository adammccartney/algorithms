$(CC) = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -g

all: build/libadio.a build/getline.o

BUILD_DIR := build

$(BUILD_DIR)/libadio.a: $(BUILD_DIR)/getline.o
	ar rcs $@ $^

$(BUILD_DIR)/getline.o: getline.c getline.h
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf build
