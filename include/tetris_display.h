#pragma once

#include <vector>
#include "constants.h"
#include "object.h"
#include "cube.h"

class TetrisDisplay : public Object
{
public:
  TetrisDisplay(float x, float y, float width);
  ~TetrisDisplay();

  void updateColours(int (*arrData)[10][40]);
  void render(SDL_Renderer *renderer) override;

private:
  Cube arrCubes[constants::MAX_WIDTH][constants::MAX_HEIGHT];
};
