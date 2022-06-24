CXX := g++
NAME := villy
BUILD_DIR := build
FLAGS := -O3

SRC != find . -type f -name '*.cpp'

compile: $(BUILD_DIR)/$(NAME)

$(BUILD_DIR)/$(NAME): $(SRC) | $(BUILD_DIR)
	$(CXX) $^ $(FLAGS) -o $@

$(BUILD_DIR):
	mkdir -p $@

.PHONY: clean compile fclean

clean:
	$(RM) -r $(BUILD_DIR)

fclean: clean
	$(RM) $(BUILD_DIR)/$(NAME)