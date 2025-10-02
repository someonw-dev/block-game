#pragma once

#include "object.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "colours.h"

class Cube : public Object
{
public:
  Cube(float x, float y, float length) : Object(x, y, length, length){
    inner = {x + BORDER, y + BORDER, length - BORDER*2, length -BORDER*2};
  }

  // default constructor mainly for arrays
  Cube() : Object(0, 0, 10, 10) {}
 ~Cube() {}

  void render(SDL_Renderer *renderer) override {
    set_render_colour(renderer, bcolour);
    SDL_RenderFillRect(renderer, &region);

    set_render_colour(renderer, icolour);
    SDL_RenderFillRect(renderer, &inner);
  }

  void set_colour(Colours new_icolour, Colours new_bcolour) {
    icolour = new_icolour;
    bcolour = new_bcolour;
  }

  void set_y(int y) {
    region.y = y;
    inner.y = y + BORDER;
  }

  void set_x(int x) {
    region.x = x;
    inner.x = x + BORDER;
  }

  void set_width(int width) {
    region.w = width;
    region.h = width;
    inner.w = width - BORDER*2;
    inner.h = width - BORDER*2;
  }

private:
  SDL_FRect inner;
  static const int BORDER = 2;
  Colours icolour = GRAY;
  Colours bcolour = BLACK;
};
