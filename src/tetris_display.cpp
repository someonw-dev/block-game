#include <SDL3/SDL_blendmode.h>
#include <SDL3/SDL_render.h>
#include "../include/tetris_display.h"
#include "../include/colour_map.h"
#include "../include/colours.h"

// the tetris board has a width of 10 cubes by 22 cubes for height (with another 18 unrendered);
TetrisDisplay::TetrisDisplay(float x, float y, float width) : Object(x, y - width * 22/10, width, width * 22/10) {
  const float LENGTH = constants::TETRIS_CUBE_WIDTH;
  std::cout << LENGTH << std::endl;

  for (int i = 0; i<constants::MAX_WIDTH; i++) {
    for (int k = 1; k<constants::MAX_HEIGHT + 1; k++) {
      arrCubes[i][k-1] = Cube(x + LENGTH*i, y - LENGTH*k, LENGTH);
      //arrCubes[i][k-1].set_colour(colour_map[0][0], colour_map[0][1]);
      arrCubes[i][k-1].set_colour(INVISIBLE, INVISIBLE);
    }
  }
}
TetrisDisplay::~TetrisDisplay() {}

void TetrisDisplay::render(SDL_Renderer *renderer) {
  // rendered first so that the other ones will draw on top of it
  SDL_SetRenderDrawColor(renderer, 40, 50, 75, 255);
  SDL_RenderFillRect(renderer, &region);

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  for (int i = 0; i<constants::MAX_WIDTH; i++) {
    for (int k = 0; k<constants::MAX_HEIGHT; k++) {
      arrCubes[i][k].render(renderer);
    }
  }
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}

// should be called anytime the board info changes
void TetrisDisplay::updateColours(int (*arrData)[10][40]) {
  for (int i = 0; i<constants::MAX_WIDTH; i++) {
    for (int k = 0; k<constants::MAX_HEIGHT; k++) {
      //arrCubes[i][k].set_colour(colour_map[(*arrData)[i][k]][0], colour_map[(*arrData)[i][k]][1]);
      if ((*arrData)[i][k] == 0) {
        arrCubes[i][k].set_colour(INVISIBLE, INVISIBLE);
        arrCubes[i][k].set_highlight(false);
      } else {
        arrCubes[i][k].set_colour(colour_map[(*arrData)[i][k]][0], BLACK);
        arrCubes[i][k].set_highlight(true);
      }
    }
  }
}
