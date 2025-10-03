#include <iostream>
#include <map>
#include "../include/tetris.h"
#include "../include/position.h"
#include "../include/object.h"
#include "../include/cube.h"
#include "../include/constants.h"
#include "../include/tetris_display.h"
#include <algorithm>
#include <vector>

int arrTetris[10][40];
TetrisDisplay display = {constants::TETRIS_X, constants::TETRIS_Y, constants::TETRIS_WIDTH};

// at first i was updating the array as the termino was moving down but then i realised
// i really just... dont have to do that lmao
Termino::Termino() : Object(0, 0, 0, 0) {
  X = 3;
  Y = 20;
  rotation = 3;
  coordinates[0] = {{0, 2}, {1, 2}, {1, 1}, {2, 1}};
  coordinates[1] = {{1, 0}, {1, 1}, {2, 1}, {2, 2}};
  coordinates[2] = {{0, 1}, {1, 1}, {1, 0}, {2, 0}};
  coordinates[3] = {{0, 0}, {0, 1}, {1, 1}, {1, 2}};
  for (Cube &i : cubes) {
    i.set_width(constants::TETRIS_CUBE_WIDTH);
    i.set_colour(RED, DARK_RED);
  }

  move_cubes();
}
Termino::~Termino() {}

// call rotate (+1/-1) rotate -> check test conditions and use first one that works -> if they all fail dont rotate
void Termino::rotate_left() {
  ++rotation;
  rotation = rotation % 4;
  move_cubes();
}

void Termino::rotate_right() {
  --rotation;
  if (rotation < 0) {
    rotation = 3;
  }
  move_cubes();
}

void Termino::rotate() {
  move_cubes();
}

void Termino::checkRotation() {}

bool Termino::move(int relative_x, int relative_y) {
  if (check_valid(X + relative_x, Y + relative_y)) {
    Y += relative_y;
    X += relative_x;

    move_cubes();
    return true;
  }

  return false;
}

void Termino::quick_place() {
  int counter = 0;
  while (check_valid(X, Y - counter)) {
    ++counter;
  }

  Y -= counter - 1;
  place_termino();
}

void Termino::move_down() {
  // if a down move is not valid it should place down the tile
  if (!move(0, -1)) {
    place_termino();
  }
}

void Termino::place_termino() {
  for (Position &i: coordinates[rotation]) {
    arrTetris[X + i.x][Y + i.y] = 1;
  }

  display.updateColours(&arrTetris);
  // move termino back up, get new termino, check for line clears
  Y = 20;
  move_cubes();
}

void Termino::render(SDL_Renderer *renderer) {

  display.render(renderer);

  // piece should be infront of everything
  for (Cube &i : cubes) {
    i.render(renderer);
  }
}

bool Termino::check_occupied(int x, int y) {
  for (Position &i: coordinates[rotation]) {
    if (arrTetris[i.x + x][i.y + y] == 1) {
      return false;
    }
  }
  return true;
}
// check if its inside the board
bool Termino::check_in_range(int x, int y) {
  for (Position &i: coordinates[rotation]) {
    //ensures it wont go below 1 too far to the left and to far to the right
    if ((i.y + y < 0) || (i.x + x < 0) || (i.x + x > 9)) {
      return false;
    }
  }

  return true;
}
bool Termino::check_valid(int x, int y) {
  // checking range first is pretty important or else you can have
  // a segmentation fault when accessing the array
  if (!check_in_range(x, y)) {
    return false;
  }

  if (!check_occupied(x, y)) {
    return false;
  }

  return true;
}

std::vector<int> Termino::get_unique_y() {
  std::vector<int> unique_y;

  for (Position &i : coordinates[rotation]) {
    // if vector doesnt contain y add y to the unique values
    if (!(std::find(unique_y.begin(), unique_y.end(), i.y) != unique_y.end())) {
      unique_y.push_back(i.y);
    }
  }

  return unique_y;
}

void Termino::move_cubes() {
  for (int i = 0; i < 4; i++) {
    cubes[i].set_x(constants::TETRIS_X + constants::TETRIS_CUBE_WIDTH*(X + coordinates[rotation][i].x));
    cubes[i].set_y(constants::TETRIS_Y - constants::TETRIS_CUBE_WIDTH*(Y + coordinates[rotation][i].y + 1));
  }
}

