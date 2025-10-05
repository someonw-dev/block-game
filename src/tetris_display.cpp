#include <SDL3/SDL_render.h>
#include <iostream>
#include "../include/tetris_display.h"
#include "../include/colour_map.h"

// the tetris board has a width of 10 cubes by 22 cubes for height (with another 18 unrendered);
TetrisDisplay::TetrisDisplay(float x, float y, float width) : Object(x, y - width * 22/10, width, width * 22/10) {
  const float LENGTH = constants::TETRIS_CUBE_WIDTH;
  std::cout << LENGTH << std::endl;

  for (int i = 0; i<constants::MAX_WIDTH; i++) {
    for (int k = 1; k<constants::MAX_HEIGHT + 1; k++) {
      arrCubes[i][k-1] = Cube(x + LENGTH*i, y - LENGTH*k, LENGTH);
      arrCubes[i][k-1].set_colour(colour_map[0][0], colour_map[0][1]);
    }
  }
}
TetrisDisplay::~TetrisDisplay() {}

void TetrisDisplay::render(SDL_Renderer *renderer) {
  // rendered first so that the other ones will draw on top of it
  SDL_RenderFillRect(renderer, &region);

  for (int i = 0; i<constants::MAX_WIDTH; i++) {
    for (int k = 0; k<constants::MAX_HEIGHT; k++) {
      arrCubes[i][k].render(renderer);
    }
  }
}

// should be called anytime the board info changes
void TetrisDisplay::updateColours(int (*arrData)[10][40]) {
  for (int i = 0; i<constants::MAX_WIDTH; i++) {
    for (int k = 0; k<constants::MAX_HEIGHT; k++) {
      arrCubes[i][k].set_colour(colour_map[(*arrData)[i][k]][0], colour_map[(*arrData)[i][k]][1]);
    }
  }
}
