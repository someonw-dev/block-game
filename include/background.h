#pragma once
#include "background_cube.h"
#include "constants.h"
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <vector>

class Background : public Object  {
public:
  Background() : Object{0, 0, 0, 0} {
    const float cube_width = constants::SCREEN_WIDTH * 0.10;

    total_x_cubes = std::ceil(constants::SCREEN_WIDTH / cube_width) + 1;
    total_y_cubes = std::ceil(constants::SCREEN_HEIGHT / cube_width) + 1;

    srand(time(NULL));

    global_x = rand() % int(cube_width);
    global_y = rand() % int(cube_width);

    for (int i = -1; i<total_y_cubes; i++) {
      Row row;

      for (int k = -1; k<total_x_cubes; k++) {
        row.push_back(BackgroundCube {global_x + k * cube_width, global_y + i * cube_width, cube_width, 10, 150 + rand() % 100, rand() % 255});
      }

      cubes.push_back(row);
    }

  }

  void render(SDL_Renderer *renderer) override {
    for (int i = 0; i < total_x_cubes; i++) {
      for (int k = 0; k < total_y_cubes; k++) {
       cubes[k][i].render(renderer);
      }
    }
  };

private:
  float global_x;
  float global_y;
  int total_x_cubes;
  int total_y_cubes;
  typedef std::vector<BackgroundCube> Row;
  std::vector<std::vector<BackgroundCube>> cubes;
};
