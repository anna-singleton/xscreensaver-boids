# this makefile is a stripped down version of this one:
# https://makefiletutorial.com/#makefile-cookbook

TARGET_EXEC := boids

CC := gcc

BUILD_DIR := ./build
SRC_DIRS := ./src

CFLAGS := -O3
LINKERFLAGS := -lm -lX11

# Find all the C files we want to compile
# Note the single quotes around the * expressions. Make will incorrectly expand these otherwise.
SRCS := $(shell find $(SRC_DIRS) -name '*.c')

# String substitution for every C file.
# As an example, hello.cpp turns into ./build/hello.cpp.o
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# The final build step.
$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) $(LINKERFLAGS) -o $(TARGET_EXEC)

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(LINKERFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -r $(BUILD_DIR)
	rm $(TARGET_EXEC)
