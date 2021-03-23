#include "maze_field.hpp"
#include "../include.hpp"

/* maze constructor
 * creating field and it first content
 */
maze_field::maze_field()
  : x_size(X_CELL_COUNT), y_size(Y_CELL_COUNT) {
  field = new cell_type[x_size * y_size];
  for (size_t i = 0; i < x_size * y_size; ++i) {
    if ((i % x_size) % 2 && (i / x_size) % 2) {
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