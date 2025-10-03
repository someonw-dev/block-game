#include <iostream>
#include <map>
#include "../include/tetris.h"
#include "../include/position.h"
#include "../include/object.h"
#include "../include/cube.h"
#include "../include/constants.h"
#include "../include/tetris_display.h"
#include "../include/terminos.h"
#include <algorithm>
#include <vector>

int arrTetris[10][40];
TetrisDisplay display = {constants::TETRIS_X, constants::TETRIS_Y, constants::TETRIS_WIDTH};

// at first i was updating the array as the termino was moving down but then i realised
// i really just... dont have to do that lmao
Tetris::Tetris() : Object(0, 0, 0, 0) {
  rotation = 0;

  X = 3;
  Y = 20;

  for (Cube &i : cubes) {
    i.set_width(constants::TETRIS_CUBE_WIDTH);
  }

  set_new_termino();
  move_cubes();
}
Tetris::~Tetris() {}

// call rotate (+1/-1) rotate -> check test conditions and use first one that works -> if they all fail dont rotate
void Tetris::rotate_left() {
  rotate(1);
}

void Tetris::rotate_right() {
  rotate(-1);
}

void Tetris::rotate(int r) {
  int wanted_rotation = rotation;
  wanted_rotation += r;

  // ensures wanted_rotation is between 0-3
  wanted_rotation %= 4;
  if (wanted_rotation < 0) {
    wanted_rotation = 3;
  }

  if (check_valid(X, Y, wanted_rotation)) {
    rotation = wanted_rotation;
    move_cubes();
  }
}

void Tetris::checkRotation() {}

bool Tetris::move(int relative_x, int relative_y) {
  if (check_valid(X + relative_x, Y + relative_y, rotation)) {
    Y += relative_y;
    X += relative_x;

    move_cubes();
    return true;
  }

  return false;
}

void Tetris::quick_place() {
  int counter = 0;
  while (check_valid(X, Y - counter, rotation)) {
    ++counter;
  }

  Y -= counter - 1;
  place_termino();
}

void Tetris::move_down() {
  // if a down move is not valid it should place down the tile
  if (!move(0, -1)) {
    place_termino();
  }
}

void Tetris::place_termino() {
  for (Position &i: termino->coordinates[rotation]) {
    arrTetris[X + i.x][Y + i.y] = 1;
  }

  display.updateColours(&arrTetris);
  // move termino back up, get new termino, check for line clears
  set_new_termino();
  Y = 20;
  X = 4;
  rotation = 0;
  move_cubes();
}

void Tetris::render(SDL_Renderer *renderer) {

  display.render(renderer);

  // piece should be infront of everything
  for (Cube &i : cubes) {
    i.render(renderer);
  }
}

bool Tetris::check_occupied(int x, int y, int r) {
  for (Position &i: termino->coordinates[r]) {
    if (arrTetris[i.x + x][i.y + y] == 1) {
      return false;
    }
  }
  return true;
}
// check if its inside the board
bool Tetris::check_in_range(int x, int y, int r) {
  for (Position &i: termino->coordinates[r]) {
    //ensures it wont go below 1 too far to the left and to far to the right
    if ((i.y + y < 0) || (i.x + x < 0) || (i.x + x > 9)) {
      return false;
    }
  }

  return true;
}
bool Tetris::check_valid(int x, int y, int r) {
  // checking range first is pretty important or else you can have
  // a segmentation fault when accessing the array out of bounds
  if (!check_in_range(x, y, r)) {
    return false;
  }

  if (!check_occupied(x, y, r)) {
    return false;
  }

  return true;
}

void Tetris::set_new_termino() {
  termino = get_next_termino();

  for (Cube &i : cubes) {
    i.set_colour(termino->inner, termino->outer);
  }
}

std::vector<int> Tetris::get_unique_y() {
  std::vector<int> unique_y;

  for (Position &i : termino->coordinates[rotation]) {
    // if vector doesnt contain y add y to the unique values
    if (!(std::find(unique_y.begin(), unique_y.end(), i.y) != unique_y.end())) {
      unique_y.push_back(i.y);
    }
  }

  return unique_y;
}

void Tetris::move_cubes() {
  for (int i = 0; i < 4; i++) {
    cubes[i].set_x(constants::TETRIS_X + constants::TETRIS_CUBE_WIDTH*(X + termino->coordinates[rotation][i].x));
    cubes[i].set_y(constants::TETRIS_Y - constants::TETRIS_CUBE_WIDTH*(Y + termino->coordinates[rotation][i].y + 1));
  }
}

