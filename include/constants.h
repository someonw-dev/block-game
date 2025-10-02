#pragma once

namespace constants {
  const int SCREEN_WIDTH = 1280;
  const int SCREEN_HEIGHT = 720;

  const float TETRIS_WIDTH = 250;
  const float TETRIS_X = (SCREEN_WIDTH/2.0f)-TETRIS_WIDTH/2;
  const float TETRIS_Y = (SCREEN_HEIGHT/2.0f)+TETRIS_WIDTH *22/20;
  // max 10 cubes on x and 22 on y
  const int MAX_WIDTH = 10;
  const int MAX_HEIGHT = 22;
  const float TETRIS_CUBE_WIDTH = TETRIS_WIDTH / MAX_WIDTH;

}
