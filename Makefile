BINNAME = maze_gen

BUILD_FLAGS = -lSDL2
GCC         = g++

MAIN_DIR = ./src
MAZE_DIR = ./src/maze

BUILD_DIR = ./build

.PHONY: all run build clean

all: build

clean:
	rm -rf $(BUILD_DIR)/*

build: $(BUILD_DIR)/main.o $(BUILD_DIR)/maze_field.o $(BUILD_DIR)/maze_controller.o
	$(GCC) $^ $(BUILD_FLAGS) -o $(BUILD_DIR)/$(BINNAME)

run: $(BUILD_DIR)/$(BINNAME)
	$(BUILD_DIR)/$(BINNAME)

$(BUILD_DIR)/main.o: $(MAIN_DIR)/*.cpp
	g++ $(BUILD_FLAGS) -c $< -o $@

$(BUILD_DIR)/maze_field.o: $(MAZE_DIR)/maze_field.cpp
	g++ $(BUILD_FLAGS) -c $< -o $@

$(BUILD_DIR)/maze_controller.o: $(MAZE_DIR)/maze_controller.cpp
	g++ $(BUILD_FLAGS) -c $< -o $@