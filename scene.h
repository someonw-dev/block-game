#pragma once

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <iostream>

class Scene {
public:
  Scene(std::string sceneTitle) {
    name = sceneTitle;

    std::cout << name + " scene created" << std::endl;
  };
  ~Scene() {
    std::cout << name + " scene destroyed" << std::endl;
  };

  virtual void init() {};
  virtual void render(SDL_Renderer *renderer) {};
  virtual void on_event(SDL_Event *event) {};
  virtual void on_resize(int w, int h) {};

private:
  int height;
  int width;
  std::string name;
};
