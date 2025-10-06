#pragma once

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <iostream>

class Object {
protected:
  SDL_FRect region;
public:
  // this is for draw order stuff
  int z_index;
  Object(float x, float y, float w, float h, int z) {
    region = {x, y, w, h};
    z_index = z;
  }
  Object(float x, float y, float w, float h) {
    region = {x, y, w, h};
    z_index = 0;
  }
  virtual ~Object() {
  };

  void set_z_axis(int z) {
    z_index = z;
  }

  void set_y(float y) {
    region.y = y;
  }

  void set_x(float x) {
    region.x = x;
  }

  float get_width() {
    return region.w;
  }

  float get_height() {
    return region.h;
  }

  virtual void render(SDL_Renderer *renderer) {};
  virtual void on_event(SDL_Event *event) {};
};
