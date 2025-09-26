#include "../components/button.h"
#include "scenemanager.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_video.h>
#include "menu.h"
#include "scene2.cpp"

void play() {
  SceneManager::getInstance().transition(std::make_unique<SceneTwo>());
}


Button btnPlay = {100, 100, 100, 100, &play};

void StartMenu::init() {
}

void StartMenu::render(SDL_Renderer *renderer) {
  btnPlay.render(renderer);
}

void StartMenu::on_event(SDL_Event *event) {
  btnPlay.on_event(event);
}

