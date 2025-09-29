#include "../include/tetris_display.h"
#include <SDL3/SDL_render.h>

// the tetris board has a width of 10 cubes by 22 cubes for height (with another 18 unrendered);
TetrisDisplay::TetrisDisplay(float x, float y, float width) : Object(x-width/2, y-width* 22/20, width, width * 22/10) {
  float actualX = x-width/2;
  float actualY = y-width *22/20;
  const float LENGTH = width / MAX_WIDTH;

  for (int i = 0; i<MAX_WIDTH; i++) {
    for (int k = 0; k<MAX_HEIGHT; k++) {
      arrCubes[i][k] = Cube(actualX + LENGTH*i, actualY + LENGTH*k, LENGTH);
    }
  }
}
TetrisDisplay::~TetrisDisplay() {}

void TetrisDisplay::render(SDL_Renderer *renderer) {
  // rendered first so that the other ones will draw on top of it
  SDL_RenderFillRect(renderer, &region);

  for (int i = 0; i<MAX_WIDTH; i++) {
    for (int k = 0; k<MAX_HEIGHT; k++) {
      arrCubes[i][k].render(renderer);
    }
  }
}

void TetrisDisplay::updateInfo(int arr[MAX_WIDTH][MAX_HEIGHT]) {

}
