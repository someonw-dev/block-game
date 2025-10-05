#pragma once

#include <array>
#include <map>
#include <vector>
#include "position.h"
#include "colours.h"

struct Termino {
  Termino();
  ~Termino();

  virtual void set_kick_data();
  // local x, y that changes based on rotation
  std::map<int, std::vector<Position>> coordinates;
  //global x, y
  int x_start;
  int y_start;

  int colour_map_key;

  std::map<std::array<int, 2>, std::vector<Position>> wall_kick_data;
};

void termino_init();
Termino* get_next_termino();
Termino* get_preview_termino();
