#include <functional>
#include <iostream>
#include <map>
#include "../include/tetris.h"
#include "../include/position.h"
#include "../include/object.h"
#include "../include/cube.h"
#include "../include/constants.h"
#include "../include/tetris_display.h"
#include "../include/terminos.h"
#include "../include/colour_map.h"
#include <algorithm>
#include <vector>

int arrTetris[10][40];
TetrisDisplay display = {constants::TETRIS_X, constants::TETRIS_Y, constants::TETRIS_WIDTH};



// at first i was updating the array as the termino was moving down but then i realised
// i really just... dont have to do that lmao
Tetris::Tetris() : Object(0, 0, 0, 0) {
  termino_init();
  rotation = 0;
  swap = true;
  level = 5;

  for (Cube &i : termino_cubes) {
    i.set_width(constants::TETRIS_CUBE_WIDTH);
    i.set_y(-50);
  }

  for (Cube &i : preview_cubes) {
    i.set_width(constants::TETRIS_CUBE_WIDTH);
    i.set_y(-50);
  }

  for (Cube &i : ghost_cubes) {
    i.set_width(constants::TETRIS_CUBE_WIDTH);
    i.set_colour(LIGHT_GRAY, GRAY);
    i.set_y(-50);
  }

  for (Cube &i : saved_cubes) {
    i.set_width(constants::TETRIS_CUBE_WIDTH);
    i.set_y(-50);
  }

  set_new_termino();
  move_cubes();
}
Tetris::~Tetris() {}

const char* Tetris::get_score() {
  // technically if you get your score to 94 digits this *could* crash but there is no way you are getting to that amount
  static char str[100];
  strcpy(str, "Score: ");
  strcat(str, std::to_string(score).c_str());
  return str;
}

// call rotate (+1/-1) rotate -> check test conditions and use first one that works -> if they all fail dont rotate
void Tetris::rotate_left() {
  rotate(-1);
}

void Tetris::rotate_right() {
  rotate(1);
}

void Tetris::rotate(int r) {
  int wanted_rotation = rotation;
  wanted_rotation += r;

  // ensures wanted_rotation is between 0-3
  wanted_rotation %= 4;
  if (wanted_rotation < 0) {
    wanted_rotation = 3;
  }

  // there are 5 tests each with 8 different test values depending on where it is rotating from
  // these values are defined in the terminos themself because the I termino has different test values
  if (check_valid(X, Y, wanted_rotation)) {
    rotation = wanted_rotation;
    move_cubes();
  } else {
    for (int i = 0; i<4; i++) {
      if (check_valid(X + termino->wall_kick_data[{rotation, wanted_rotation}][i].x,
                      Y + termino->wall_kick_data[{rotation, wanted_rotation}][i].y,
                      wanted_rotation))
      {
        X += termino->wall_kick_data[{rotation, wanted_rotation}][i].x;
        Y += termino->wall_kick_data[{rotation, wanted_rotation}][i].y;
        rotation = wanted_rotation;
        move_cubes();
        // first valid set of coords is where it should be placed
        break;
      }
    }
  }

  // if none of the checks pass it fails completely and doesnt rotate
}

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
  int drop = get_y_intersect();
  score += drop*2;
  Y -= drop;
  place_termino();
}

bool Tetris::next_down_is_place()
{
  if (check_valid(X, Y - 1, rotation)) {
    return true;
  }

  return false;
}
void Tetris::move_down() {
  // if a down move is not valid it should place down the tile
  if (!move(0, -1)) {
    place_termino();
  }
}

void Tetris::place_termino() {
  for (Position &i: termino->coordinates[rotation]) {
    arrTetris[X + i.x][Y + i.y] = termino->colour_map_key;
  }

  clear_row();
  display.updateColours(&arrTetris);

  swap = true;
  // move termino back up, get new termino, check for line clears
  set_new_termino();
  move_cubes();
}

void Tetris::clear_row() {
  std::vector<int> rows = get_unique_y();

  int counter = 0;
  for (int &i: rows) {
    bool filled = true;
    for (int k = 0; k<constants::MAX_WIDTH; k++) {
      if (arrTetris[k][i] == 0) {
        filled = false;
        break;
      }
    }

    if (filled) {
      ++counter;
      for (int k = i; k<constants::MAX_HEIGHT - 1; k++) {
        for (int j = 0; j<constants::MAX_WIDTH; j++) {
          arrTetris[j][k] = arrTetris[j][k + 1];
        }
      }
    }
  }

  switch (counter) {
    case 1: {
      score += 100 * level;
      break;
    }
    case 2: {
      score += 300 * level;
      break;
    }
    case 3: {
      score += 500 * level;
      break;
    }
    case 4: {
      score += 800 * level;
      break;
    }
  }
}


void Tetris::swap_active_piece() {
  // if there is a saved termino
  if (swap) {
    //doesnt let you swap again until the next piece is placed
    swap = false;
    if (saved_termino) {
      Termino *temp = termino;
      termino = saved_termino;
      saved_termino = temp;

      Y = termino->y_start;
      X = termino->x_start;
      rotation = 0;

      set_termino_colours();
      move_cubes();
    } else {
      // if there isnt a saved termino
      saved_termino = termino;
      set_new_termino();
      move_cubes();
    }
    const float SAVED_X = constants::TETRIS_X - constants::TETRIS_CUBE_WIDTH * 4 - 30;
    for (int i = 0; i < 4; i++) {
      saved_cubes[i].set_x(SAVED_X + constants::TETRIS_CUBE_WIDTH*(saved_termino->coordinates[0][i].x));
      saved_cubes[i].set_y(200 - constants::TETRIS_CUBE_WIDTH*(saved_termino->coordinates[0][i].y));
      saved_cubes[i].set_colour(colour_map[saved_termino->colour_map_key][0], colour_map[saved_termino->colour_map_key][1]);
    }
  }

}


void Tetris::render(SDL_Renderer *renderer) {

  display.render(renderer);


  for (Cube &i : preview_cubes) {
    i.render(renderer);
  }
  for (Cube &i : saved_cubes) {
    i.render(renderer);
  }

  for (Cube &i : ghost_cubes) {
    i.render(renderer);
  }

  // piece should be infront of everything
  for (Cube &i : termino_cubes) {
    i.render(renderer);
  }
}

int Tetris::get_y_intersect() {
  int counter = 0;
  while (check_valid(X, Y - counter, rotation)) {
    ++counter;
  }

  return counter - 1;
}

bool Tetris::check_occupied(int x, int y, int r) {
  for (Position &i: termino->coordinates[r]) {
    if (arrTetris[i.x + x][i.y + y] != 0) {
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

void Tetris::set_termino_colours() {
  for (Cube &i : termino_cubes) {
    i.set_colour(colour_map[termino->colour_map_key][0], colour_map[termino->colour_map_key][1]);
  }

  for (Cube &i : preview_cubes) {
    i.set_colour(colour_map[preview->colour_map_key][0], colour_map[preview->colour_map_key][1]);
  }
}

void Tetris::set_new_termino() {
  termino = get_next_termino();
  preview = get_preview_termino();

  set_termino_colours();

  if (!check_valid(termino->x_start, termino->y_start, 0)) {
    std::cout << "you lost :(" << std::endl;
  }

  Y = termino->y_start;
  X = termino->x_start;
  rotation = 0;

  const float PREVIEW_X = constants::TETRIS_X + constants::TETRIS_WIDTH + 30;
  for (int i = 0; i < 4; i++) {
    preview_cubes[i].set_x(PREVIEW_X + constants::TETRIS_CUBE_WIDTH*(preview->coordinates[rotation][i].x));
    preview_cubes[i].set_y(200 - constants::TETRIS_CUBE_WIDTH*(preview->coordinates[rotation][i].y));
  }

}

std::vector<int> Tetris::get_unique_y() {
  std::vector<int> unique_y;

  for (Position &i : termino->coordinates[rotation]) {
    // if vector doesnt contain new y add new y to the unique values
    if (!(std::find(unique_y.begin(), unique_y.end(), i.y + Y) != unique_y.end())) {
      unique_y.push_back(i.y + Y);
    }
  }

  std::sort(unique_y.begin(), unique_y.end(), std::greater<int>());

  return unique_y;
}

void Tetris::move_cubes() {
  for (int i = 0; i < 4; i++) {
    termino_cubes[i].set_x(constants::TETRIS_X + constants::TETRIS_CUBE_WIDTH*(X + termino->coordinates[rotation][i].x));
    termino_cubes[i].set_y(constants::TETRIS_Y - constants::TETRIS_CUBE_WIDTH*(Y + termino->coordinates[rotation][i].y + 1));
  }

  // get y intersect is kinda a bad name because it actually gets the y difference
  int ydif = get_y_intersect();

  for (int i = 0; i < 4; i++) {
    ghost_cubes[i].set_x(constants::TETRIS_X + constants::TETRIS_CUBE_WIDTH*(X + termino->coordinates[rotation][i].x));
    ghost_cubes[i].set_y(constants::TETRIS_Y - constants::TETRIS_CUBE_WIDTH*(Y + termino->coordinates[rotation][i].y + 1 - ydif));
  }
}

