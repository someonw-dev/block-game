#pragma once

#include "scene.h"
#include "button.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <iostream>
#include "scenemanager.h"
#include "menu.h"

void returntomenu() {
  std::cout << "welcome to ball 69!!!" << std::endl;
  SceneManager::getInstance().transition(std::make_unique<StartMenu>());
}

class Ball69 : public Scene {
  Button btnReturn = {200, 100, 100, 100, &returntomenu};

public:
  Ball69() : Scene("Ball69") {};

  SDL_FRect button_rect = {200, 0, 100, 100};
  SDL_FRect button_rect1 = {100, 0, 100, 100};
  SDL_FRect button_rect2 = {300, 0, 100, 100};
  SDL_FRect button_rect3 = {200, 200, 100, 100};

  void render(SDL_Renderer *renderer) override {
    btnReturn.render(renderer);
    SDL_SetRenderDrawColor(renderer, 10, 10, 255, 255);
    SDL_RenderFillRect(renderer, &button_rect);
    SDL_RenderFillRect(renderer, &button_rect1);
    SDL_RenderFillRect(renderer, &button_rect2);
    SDL_RenderFillRect(renderer, &button_rect3);
  }

  void on_event(SDL_Event *event) override {
    btnReturn.on_event(event);
  }

};
