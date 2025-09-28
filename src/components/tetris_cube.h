#include "object.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

class Cube : public Object
{
public:
  Cube(float x, float y, float length) : Object(x, y, length, length){
    inner = {x + BORDER, y + BORDER, length - BORDER*2, length -BORDER*2};
  }
  ~Cube() {};

  void render(SDL_Renderer *renderer) override {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &region);

    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderFillRect(renderer, &inner);
  }
private:
  SDL_FRect inner;
  const int BORDER = 2;
};
