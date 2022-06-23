CC := g++
FLAGS := -o
NAME := villy
BUILD_DIR := build

make_dir:
	mkdir -p $(BUILD_DIR)

compile: *.cpp
	$(CC) $^ $(FLAGS) $(BUILD_DIR)/$(NAME)

build: make_dir compile

.PHONY: clean

clean: 
	rm -rf $(BUILD_DIR)
