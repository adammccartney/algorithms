CC = gcc
CFLAGS := -fPIC -std=c99 -g -fPIC -Wall -Wextra -Werror -pedantic
LDFLAGS := -shared

SRC_DIR := src
BUILD_DIR := build

HEADERS := $(wildcard $(SRC_DIR)/*.h)
SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(addprefix $(BUILD_DIR)/, $(notdir $(SOURCES:.c=.o)))

# Link the shared library
$(BUILD_DIR)/adlib.so: $(OBJECTS)
	@ printf "%8s %-40s %s\n" $(CC) $@ "$(CFLAGS)"
	@ mkdir -p build
	@ $(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@ printf "%8s %-40s %s\n" $(CC) $< "$(CFLAGS)"
	@ mkdir -p $(BUILD_DIR)
	@ $(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

.PHONY: default clean

clean:
	rm -rf $(BUILD_DIR)
