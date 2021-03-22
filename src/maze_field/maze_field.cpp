#include "maze_field.hpp"
#include "../include.hpp"

maze_field::maze_field()
  : x_size(X_CELL_COUNT), y_size(Y_CELL_COUNT) {
  field = new char[x_size * y_size];
  for (size_t i = 0; i < x_size * y_size; ++i) {
    if ((i % y_size) % 2 && (i / y_size) % 2) {
      field[i] = cell_type::empty;
    } else {
      field[i] = cell_type::wall;
    }
  }

  x_cell_size = WINDOW_WIDTH / x_size;
  y_cell_size = WINDOW_HEIGHT / y_size;
}

maze_field::~maze_field() {
  delete[] field;
}

void maze_field::render(SDL_Renderer * renderer) {
  SDL_Rect cell_box = {0, 0, x_cell_size, y_cell_size};

  for (size_t i = 0; i < x_size * y_size; ++i) {
    cell_box.x = i % y_size * x_cell_size;
    cell_box.y = i / y_size * y_cell_size;

    if (field[i] == cell_type::wall) {
      SDL_SetRenderDrawColor(renderer, 33, 33, 33, 255);
    } else {
      SDL_SetRenderDrawColor(renderer, 3, 169, 244, 255);
    }
    
    SDL_RenderFillRect(renderer, &cell_box);
  }
}