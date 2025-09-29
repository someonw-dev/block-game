#include "object.h"
#include "tetris_cube.h"
#include <vector>

class TetrisDisplay : public Object
{
public:
  TetrisDisplay(float x, float y, float width);
  ~TetrisDisplay();

  static const int MAX_WIDTH = 10;
  static const int MAX_HEIGHT = 22;

  void updateInfo(int arr[MAX_WIDTH][MAX_HEIGHT]);
  void render(SDL_Renderer *renderer) override;

private:
  int arrData[MAX_WIDTH][MAX_HEIGHT] = {0};
  Cube arrCubes[MAX_WIDTH][MAX_HEIGHT];
};
