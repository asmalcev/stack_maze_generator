#include <iostream>
#include <SDL2/SDL.h>

enum cell_type {
  empty,
  wall
};

class maze_field {
protected:
  size_t x_size;
  size_t y_size;
  char * field;

  unsigned int x_cell_size;
  unsigned int y_cell_size;

public:
  maze_field();
  ~maze_field();

  void render(SDL_Renderer * renderer);
};