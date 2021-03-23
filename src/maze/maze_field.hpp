#include <iostream>

enum cell_type {
  empty,
  wall
};

// structure that stores the entire maze field
struct maze_field {
  size_t x_size;
  size_t y_size;

  cell_type * field;

  unsigned int x_cell_size;
  unsigned int y_cell_size;

  maze_field();
  ~maze_field();
};