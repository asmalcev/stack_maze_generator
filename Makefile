BINNAME = maze_gen

BUILD_FLAGS = -lSDL2
GCC         = g++

MAIN_DIR = ./src
MAZE_DIR = ./src/maze_field

BUILD_DIR = ./build

.PHONY: all run build clean

all: build

clean:
	rm -rf $(BUILD_DIR)/*

build: $(BUILD_DIR)/main.o $(BUILD_DIR)/maze.o
	$(GCC) $^ $(BUILD_FLAGS) -o $(BUILD_DIR)/$(BINNAME)

run: $(BUILD_DIR)/$(BINNAME)
	$(BUILD_DIR)/$(BINNAME)

$(BUILD_DIR)/main.o: $(MAIN_DIR)/*.cpp
	g++ $(BUILD_FLAGS) -c $< -o $@

$(BUILD_DIR)/maze.o: $(MAZE_DIR)/*.cpp
	g++ $(BUILD_FLAGS) -c $< -o $@