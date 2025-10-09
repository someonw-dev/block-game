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
    highlight1 = {x + BORDER, y + BORDER, HIGHLIGHT_WIDTH, HIGHLIGHT_WIDTH*2};
    highlight2 = {x + BORDER + HIGHLIGHT_WIDTH, y + BORDER, HIGHLIGHT_WIDTH, HIGHLIGHT_WIDTH};
  }

  // default constructor mainly for arrays
  Cube() : Object(0, 0, 10, 10) {
  }
 ~Cube() {}

  void render(SDL_Renderer *renderer) override {
    set_render_colour(renderer, bcolour);
    SDL_RenderFillRect(renderer, &region);

    set_render_colour(renderer, icolour);
    SDL_RenderFillRect(renderer, &inner);

    if (highlight) {
      set_render_colour(renderer, WHITE);
      SDL_RenderFillRect(renderer, &highlight1);
      SDL_RenderFillRect(renderer, &highlight2);
    }
  }

  void set_highlight(bool enable_highlight) {
    highlight = enable_highlight;
  }

  void set_colour(Colours new_icolour, Colours new_bcolour) {
    icolour = new_icolour;
    bcolour = new_bcolour;
  }

  void set_y(int y) {
    region.y = y;
    inner.y = y + BORDER;
    highlight1.y = y + BORDER;
    highlight2.y = y + BORDER;
  }

  void set_x(int x) {
    region.x = x;
    inner.x = x + BORDER;
    highlight1.x = x + BORDER;
    highlight2.x = x + BORDER + HIGHLIGHT_WIDTH;
  }

  void set_width(int width) {
    region.w = width;
    region.h = width;
    inner.w = width - BORDER*2;
    inner.h = width - BORDER*2;
    highlight1.w = HIGHLIGHT_WIDTH;
    highlight1.h = HIGHLIGHT_WIDTH*2;
    highlight2.w = HIGHLIGHT_WIDTH;
    highlight2.h = HIGHLIGHT_WIDTH;
  }

private:
  SDL_FRect inner;
  SDL_FRect highlight1;
  SDL_FRect highlight2;
  bool highlight = false;
  static const int HIGHLIGHT_WIDTH = 4;
  static const int BORDER = 3;
  Colours icolour = GRAY;
  Colours bcolour = BLACK;
};
