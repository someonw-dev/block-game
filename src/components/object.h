#pragma once

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include "align.h"

class Object {
public:
  Object(Alignment align, int x, int y, int w, int h) {};
  ~Object() {};

  virtual void render(SDL_Renderer *renderer) {};
  virtual void on_event(SDL_Event *event) {};

  // TODO: resizability
  virtual void on_resize(int window_w, int window_h) {};

private:

};
