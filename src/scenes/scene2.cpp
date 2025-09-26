#pragma once

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <iostream>
#include "scenemanager.h"
#include "scene.h"
#include "../components/button.h"
#include "menu.h"

void gotoball69() {
  std::cout << "huh" << std::endl;
  SceneManager::getInstance().transition(std::make_unique<StartMenu>());
}

class SceneTwo : public Scene {
  Button btnReturn = {100, 200, 100, 100, &gotoball69};

public:
  SceneTwo() : Scene("Play") {};
  void render(SDL_Renderer *renderer) override {
    btnReturn.render(renderer);
  }

  void on_event(SDL_Event *event) override {
    btnReturn.on_event(event);
  }

};
