#pragma once

#include <vector>
#include <map>
#include "../include/tetris.h"
#include "../include/position.h"
#include "../include/object.h"
#include "../include/cube.h"
#include "../include/constants.h"

// at first i was updating the array as the termino was moving down but then i realised
// i really just... dont have to do that lmao
class Termino : Object {
public:
  Termino();
  ~Termino();

  // rotate -> check test conditions if one works use that one -> if they all fail
  void rotate_left();
  void rotate_right();
  void rotate();
  void checkRotation();
  bool move(int relative_x, int relative_y);
  void move_left();
  void move_right();
  void move_down();
  void place_termino();
  void render(SDL_Renderer *renderer) override;

private:
  bool check_occupied(int x, int y);
  bool check_in_range(int x, int y);
  bool check_valid(int x, int y);

  void move_cubes();

  int rotation;
  // local x, y that changes based on rotation
  std::map<int, std::vector<Position>> coordinates;
  //global x, y
  Cube cubes[4];
  int X;
  int Y;
};
