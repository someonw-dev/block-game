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
    std::cout << "OBJECT CREATED" << std::endl;
  }
  Object(float x, float y, float w, float h) {
    region = {x, y, w, h};
    z_index = 0;
    std::cout << "OBJECT CREATED" << std::endl;
  }
  ~Object() {
    std::cout << "OBJECT MURDERED" << std::endl;
  };

  virtual void render(SDL_Renderer *renderer) {};
  virtual void on_event(SDL_Event *event) {};
};
