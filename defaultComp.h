#pragma once

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>

enum Alignment {
  ABSOLUTE,
  LEFT,
  RIGHT,
  BOTTOM,
  TOP,
};

class DefaultComp {
public:
  DefaultComp(Alignment align, int x, int y, int w, int h) {};
  ~DefaultComp() {};

  virtual void render(SDL_Renderer *renderer) {};
  virtual void on_event(SDL_Event *event) {};
  virtual void on_resize(int window_w, int window_h) {};

private:

};
