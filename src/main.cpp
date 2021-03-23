#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "include.hpp"
#include "maze/maze_controller.hpp"

int main() {
  /*
   *
   * Init systems
   *
   *
  */
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Window   * window;
  SDL_Renderer * renderer;
  if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer) < 0) {
    std::cout << "Failed at SDL_CreateWindowAndRenderer" << std::endl;
    SDL_Quit();
    return 1;
  }
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetWindowTitle(window, "Generator");

  maze_controller maze(renderer);

  /*
   *
   * Runtime cycle
   *
   *
  */
  SDL_Event e;
  bool running = true;

  while (running) {
    SDL_RenderClear(renderer);
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        running = false;
        break;
      }
      if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE) {
        running = false;
        break;
      }
    }

    maze.update();
    maze.render();

    SDL_RenderPresent(renderer);
    // SDL_Delay(16);
    SDL_Delay(100);
  }

  /*
   *
   * Free systems
   *
   *
  */
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}