#pragma once

#include "scene.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>

class TetrisScene : public Scene {
public:
  // constructors/destructors
  TetrisScene();
  ~TetrisScene();

  void init() override;
  void on_render(SDL_Renderer *renderer) override;
  void on_event(SDL_Event *event) override;
};
