#include <iostream>
#include <map>
#include <vector>
#include "../include/tetris.h"
#include "../include/position.h"
#include "../include/object.h"
#include "../include/cube.h"
#include "../include/constants.h"

int arrTetritTest[10][40];

// at first i was updating the array as the termino was moving down but then i realised
// i really just... dont have to do that lmao
Termino::Termino() : Object(0, 0, 0, 0) {
  X = 3;
  Y = 19;
  rotation = 0;
  coordinates[0] = {{1, 3}, {2, 3}, {2, 2}, {3, 2}};
  for (Cube &i : cubes) {
    i.set_width(constants::TETRIS_CUBE_WIDTH);
    i.set_colour(RED, DARK_RED);
  }

  move_cubes();
}
Termino::~Termino() {}

// rotate -> check test conditions if one works use that one -> if they all fail
void Termino::rotate_left() {};
void Termino::rotate_right() {};
void Termino::rotate() {};
void Termino::checkRotation() {};
bool Termino::move(int relative_x, int relative_y) {
  if (check_valid(X + relative_x, Y + relative_y)) {
    Y += relative_y;
    X += relative_x;

    return true;
    move_cubes();
  } else {
    std::cout << "not valid" << std::endl;
    return false;
  }
}

void Termino::move_left() {};
void Termino::move_right() {};
void Termino::move_down() {
  move(0, -1);
};

void Termino::place_termino() {

};

void Termino::render(SDL_Renderer *renderer) {
  for (Cube &i : cubes) {
    i.render(renderer);
  }
}

bool Termino::check_occupied(int x, int y) {
  for (Position &i: coordinates[rotation]) {
    if (i.y + x < 0) {
      return false;
    }
  }
  return true;
}
// check if its inside the board
bool Termino::check_in_range(int x, int y) {
  for (Position &i: coordinates[rotation]) {
    //ensures it wont go below 1 too far to the left and to far to the right
    if ((i.y + y < 1) || (i.x + x < 0) || (i.x + x > 9)) {
      return false;
    }
  }

  return true;
}
bool Termino::check_valid(int x, int y) {
  if (check_in_range(x, y)) {
    return true;
  }

  return false;
}

void Termino::move_cubes() {
  for (int i = 0; i < 4; i++) {
    cubes[i].set_x(constants::TETRIS_X + constants::TETRIS_CUBE_WIDTH*(X + coordinates[rotation][i].x));
    cubes[i].set_y(constants::TETRIS_Y + constants::TETRIS_CUBE_WIDTH*(-Y - coordinates[rotation][i].y));
  }
}

