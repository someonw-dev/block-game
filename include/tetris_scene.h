#pragma once

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>
#include "text.h"
#include "scene.h"

class TetrisScene : public Scene {
public:
  // constructors/destructors
  TetrisScene();
  ~TetrisScene();

  void init() override;
  void update() override;
  void on_render(SDL_Renderer *renderer) override;
  void on_event(SDL_Event *event) override;
  void pause_init();
  void shared_init();
  void lost_init();

  std::vector<Object*> paused_objects;
  std::vector<Object*> lost_objects;
  // objects only visible before youve started playing
  std::vector<Object*> first_objects;
  // objects visible before and whilst youve lost
  std::vector<Object*> shared_objects;


  void push_paused_object(Object *obj) {
    paused_objects.push_back(obj);
  }

  void push_lost_object(Object *obj) {
    lost_objects.push_back(obj);
  }

  void push_first_object(Object *obj) {
    first_objects.push_back(obj);
  }

  void push_shared_object(Object *obj) {
    shared_objects.push_back(obj);
  }

  int arrData[10][40] = {0};

private:
  // Main stuff
  Text *score;
  Text *level;
  Text *lines_needed;

  // Statistics

  // Highscore
};
