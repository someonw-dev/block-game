#pragma once

#include <vector>
#include <map>
#include "../include/tetris.h"
#include "../include/position.h"
#include "../include/object.h"
#include "../include/cube.h"
#include "../include/constants.h"
#include "terminos.h"

// at first i was updating the array as the termino was moving down but then i realised
// i really just... dont have to do that lmao
class Tetris : Object {
public:
  Tetris();
  ~Tetris();

  // rotate -> check test conditions if one works use that one -> if they all fail
  void rotate_left();
  void rotate_right();
  void rotate(int r);
  void checkRotation();
  bool move(int relative_x, int relative_y);
  void quick_place();
  void move_down();
  void place_termino();
  void render(SDL_Renderer *renderer) override;
  void swap_active_piece();

private:
  std::vector<int> get_unique_y();
  bool check_occupied(int x, int y, int r);
  bool check_in_range(int x, int y, int r);
  bool check_valid(int x, int y, int r);
  int get_y_intersect();

  void set_termino_colours();
  void set_new_termino();
  void move_cubes();
  void clear_row();

  int rotation;
  Termino *termino;
  Cube termino_cubes[4];
  Termino *saved_termino;
  Cube saved_cubes[4];
  Termino *preview;
  Cube preview_cubes[4];
  Termino *ghost;
  Cube ghost_cubes[4];
  //global x, y
  int X;
  int Y;
};
