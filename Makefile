# Compiler and tools
CC := $(shell which gcc)
AR := $(shell which ar)
RM := $(shell which rm)

# Compiler flags
CFLAGS := -Wall -Wextra -Werror -O3 -std=c99 -Iinclude

# Directories
INCLUDE_DIR := include
SRC_DIR := src
BUILD_DIR := build
TEST_DIR := tests
EXAMPLE_DIR := examples

# Target library
TARGET_LIB := libbm.a

# Source and header files
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))
HEADER_FILES := $(wildcard $(INCLUDE_DIR)/*.h)

# Unit test files
TEST_SRC_FILES := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ_FILES := $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%.o, $(TEST_SRC_FILES))
TEST_TARGET := test_suite

# Example files
EXAMPLE_SRC_FILES := $(wildcard $(EXAMPLE_DIR)/example_bm.c)
EXAMPLE_OBJ_FILES := $(patsubst $(EXAMPLE_DIR)/%.c, $(BUILD_DIR)/%.o, $(EXAMPLE_SRC_FILES))
EXAMPLE_TARGETS := $(patsubst $(BUILD_DIR)/%.o, $(BUILD_DIR)/%, $(EXAMPLE_OBJ_FILES))

# Default target
all: $(TARGET_LIB) examples tests

# Build the static library
$(TARGET_LIB): $(OBJ_FILES)
	$(AR) rcs $@ $^

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER_FILES)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile test files
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c $(HEADER_FILES)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Link test executable
$(TEST_TARGET): $(OBJ_FILES) $(TEST_OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/$@

# Compile example files
$(BUILD_DIR)/%.o: $(EXAMPLE_DIR)/%.c $(HEADER_FILES)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Build examples
examples: $(EXAMPLE_TARGETS)

$(BUILD_DIR)/%: $(BUILD_DIR)/%.o $(TARGET_LIB)
	$(CC) $(CFLAGS) $< -L. -lbm -o $@

# Run unit tests
tests: $(TEST_TARGET)
	./$(BUILD_DIR)/$(TEST_TARGET)

# Clean build files
clean:
	$(RM) -rf $(BUILD_DIR) $(TARGET_LIB)

.PHONY: all clean tests examples

