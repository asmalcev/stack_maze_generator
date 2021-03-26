#include <iostream>
#include <stack>
#include <array>
#include <ctime>
#include <SDL2/SDL.h>

#include "maze_field.hpp"

class maze_controller {
protected:
  maze_field   * _maze;
  SDL_Renderer * renderer;
  std::stack<size_t> visited_indexes;

  std::array<size_t, 5> get_neighbors_array(size_t index);
  bool is_visited(size_t index);
  size_t random_index_from_0_to(size_t divider);
  void create_path(size_t index_from, size_t index_to);

public:
  maze_controller(SDL_Renderer * renderer);
  ~maze_controller();

  void render();
  bool update();
};