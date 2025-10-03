#pragma once

#include <map>
#include <vector>
#include "position.h"
#include "colours.h"

struct Termino {
  Termino() {}
  ~Termino() {}
  // local x, y that changes based on rotation
  std::map<int, std::vector<Position>> coordinates;
  //global x, y
  int x_start;
  int y_start;

  Colours inner;
  Colours outer;
};

Termino* get_next_termino();
Termino* get_preview_termin();
