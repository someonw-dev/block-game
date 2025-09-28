#pragma once

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <memory>
#include <vector>
#include <iostream>
#include "../components/object.h"

class Scene {
public:
  Scene(std::string sceneTitle) {
    name = sceneTitle;

    std::cout << name + " scene created" << std::endl;
  };
  virtual ~Scene() {
    // ensures that there wont be a memory leak
    for (Object *i : objects) {
      delete i;
    }

    std::cout << name + " scene destroyed" << std::endl;
  };


  void render_handler(SDL_Renderer *renderer) {
    for (Object *i : objects) {
      i->render(renderer);
    }

    on_render(renderer);
  }
  void event_handler(SDL_Event *event) {
    for (Object *i : objects) {
      i->on_event(event);
    }

    on_event(event);
  }

  virtual void init() {};
  virtual void on_render(SDL_Renderer *renderer) {};
  virtual void on_event(SDL_Event *event) {};

protected:
  std::vector<Object*> objects;

  void push_obj(Object *obj) {
    objects.push_back(obj);
  };

private:
  int height = 0;
  int width = 0;
  std::string name = "Default";
};
