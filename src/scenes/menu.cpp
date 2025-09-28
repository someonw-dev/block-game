#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>
#include "scenemanager.h"
#include "menu.h"
#include "scene.h"
#include "tetris_scene.h"
#include "../components/button.h"
#include "../constants.h"

// constructor
StartMenu::StartMenu() : Scene("Menu") {
  init();
}
StartMenu::~StartMenu() {}

void play() {
  std::cout << "play" << std::endl;
  SceneManager::getInstance().transition(std::make_unique<TetrisScene>());
}

void settings() {
  std::cout << "settings" << std::endl;
}

void quit() {
  std::cout << "quit" << std::endl;
  //SceneManager::getInstance().quit();
}

void StartMenu::init() {
  const float centerX = constants::SCREEN_WIDTH / 2.0;
  const float centerY = constants::SCREEN_HEIGHT / 2.0;

  const float WIDTH = 150;
  const float HEIGHT = 60;

  Button *btnPlay = new Button(centerX - 100, centerY - 50, WIDTH, HEIGHT, &play);
  push_obj(btnPlay);

  Button *btnSettings = new Button(centerX - 100, centerY + 50, WIDTH, HEIGHT, &settings);
  push_obj(btnSettings);

  Button *btnQuit = new Button(centerX - 100, centerY + 150, WIDTH, HEIGHT, &quit);
  push_obj(btnQuit);
}

void StartMenu::on_render(SDL_Renderer *renderer) {
}

void StartMenu::on_event(SDL_Event *event) {
}

