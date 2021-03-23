#include "maze_controller.hpp"

maze_controller::maze_controller(SDL_Renderer * renderer)
  : renderer(renderer) {
  _maze = new maze_field;
  visited_indexes.push(_maze->x_size + 1);
  srand(time(0));
}

maze_controller::~maze_controller() {
  delete _maze;
}

// render field
void maze_controller::render() {
  SDL_Rect cell_box = {0, 0, _maze->x_cell_size, _maze->y_cell_size};

  for (size_t i = 0; i < _maze->x_size * _maze->y_size; ++i) {
    cell_box.x = i % _maze->x_size * _maze->x_cell_size;
    cell_box.y = i / _maze->x_size * _maze->y_cell_size;

    if (_maze->field[i] == cell_type::wall) {
      SDL_SetRenderDrawColor(renderer, 33, 33, 33, 255);
    } else {
      SDL_SetRenderDrawColor(renderer, 3, 169, 244, 255);
    }

    SDL_RenderFillRect(renderer, &cell_box);
  }
}

// update state of field
void maze_controller::update() {
  if (visited_indexes.empty()) {
    return;
  }
  size_t current_index = visited_indexes.top();

  auto neighbors = get_neighbors_array(current_index);
  while (neighbors[4] == 0) {
    visited_indexes.pop();
    if (visited_indexes.empty()) {
      return;
    }
    current_index = visited_indexes.top();
    neighbors = get_neighbors_array(current_index);
  }

  size_t index_to_visit = neighbors[ random_index_from_0_to(neighbors[4]) ];
  visited_indexes.push(index_to_visit);

  create_path(current_index, index_to_visit);
}

// generates unvisited neighbors array
std::array<size_t, 5> maze_controller::get_neighbors_array(size_t index) {
  std::array<size_t, 5> neighbors = {0};
  size_t current_index = 0;
  long index_to_check = index - 2 * _maze->x_size;

  if (index_to_check >= 0 &&
      _maze->field[index_to_check] == cell_type::empty &&
      !is_visited(index_to_check)) {
    neighbors[current_index++] = index_to_check;
  }

  index_to_check = index + 2;
  if (index_to_check >= 0 &&
      _maze->field[index_to_check] == cell_type::empty &&
      !is_visited(index_to_check)) {
    neighbors[current_index++] = index_to_check;
  }

  index_to_check = index + 2 * _maze->x_size;
  if (index_to_check >= 0 &&
      _maze->field[index_to_check] == cell_type::empty &&
      !is_visited(index_to_check)) {
    neighbors[current_index++] = index_to_check;
  }

  index_to_check = index - 2;
  if (index_to_check >= 0 &&
      _maze->field[index_to_check] == cell_type::empty &&
      !is_visited(index_to_check)) {
    neighbors[current_index++] = index_to_check;
  }

  neighbors[4] = current_index;
  return neighbors;
}

/*
 * check if point has been visited
 * if point has path to any other point -> it has been visited
 */
bool maze_controller::is_visited(size_t index) {
  long index_to_check = index - _maze->x_size;
  if (index_to_check > 0 && _maze->field[index_to_check] == cell_type::empty) {
    return true;
  }

  index_to_check = index + 1;
  if (index_to_check > 0 && _maze->field[index_to_check] == cell_type::empty) {
    return true;
  }

  index_to_check = index + _maze->x_size;
  if (index_to_check > 0 && _maze->field[index_to_check] == cell_type::empty) {
    return true;
  }

  index_to_check = index - 1;
  if (index_to_check > 0 && _maze->field[index_to_check] == cell_type::empty) {
    return true;
  }

  return false;
}

size_t maze_controller::random_index_from_0_to(size_t divider) {
  return rand() % divider;
}

// connect two cells
void maze_controller::create_path(size_t index_from, size_t index_to) {
  _maze->field[index_from + (index_to - index_from) / 2] = cell_type::empty;
}
