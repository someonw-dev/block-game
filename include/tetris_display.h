#pragma once

#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <vector>
#include "constants.h"
#include "object.h"
#include "cube.h"
#include "position.h"

class TetrisDisplay : public Object
{
public:
  TetrisDisplay(float x, float y, float width, int (*arrTetris)[10][40]);
  ~TetrisDisplay();

  void flash_and_update(int (*y_values)[4]);
  void update_colours();
  void render(SDL_Renderer *renderer) override;

private:
  Cube arrCubes[constants::MAX_WIDTH][constants::MAX_HEIGHT];
  int (*arrData)[10][40];
  Uint64 start = 0;
  Uint64 end = 0;
  const int FLASH_TIME = 200;
  bool update = true;
};
