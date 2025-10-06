#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>
#include <memory>
#include "../include/scenemanager.h"
#include "../include/menu.h"
#include "../include/scene.h"
#include "../include/tetris_scene.h"
#include "../include/button.h"
#include "../include/constants.h"
#include "../include/text.h"

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

  // pushes a quit event
  SDL_Event event;
  SDL_zero(event);
  event.type = SDL_EVENT_QUIT;
  SDL_PushEvent(&event);
}

void StartMenu::init() {
  const float centerX = constants::SCREEN_WIDTH / 2.0;
  const float centerY = constants::SCREEN_HEIGHT / 2.0;

  const float WIDTH = 150;
  const float HEIGHT = 60;
  const float BUTTON_CENTER = centerX - WIDTH * 0.5;

  Button *btnPlay = new Button(BUTTON_CENTER, centerY - 50, WIDTH, HEIGHT, &play);
  btnPlay->set_text(std::make_unique<Text>("PLAY", 0, 0, 65, SceneManager::getInstance().get_renderer()));
  push_obj(btnPlay);

  Button *btnSettings = new Button(BUTTON_CENTER, centerY + 50, WIDTH, HEIGHT, &settings);
  btnSettings->set_text(std::make_unique<Text>("SETTINGS", 0, 0, 120, SceneManager::getInstance().get_renderer()));
  push_obj(btnSettings);

  Button *btnQuit = new Button(BUTTON_CENTER, centerY + 150, WIDTH, HEIGHT, &quit);
  btnQuit->set_text(std::make_unique<Text>("QUIT", 0, 0, 65, SceneManager::getInstance().get_renderer()));
  push_obj(btnQuit);

  const float TEXT_WIDTH = 400;
  Text *title = new Text("TETRIS", centerX - TEXT_WIDTH * 0.5, 100, TEXT_WIDTH, SceneManager::getInstance().get_renderer());
  push_obj(title);
}

void StartMenu::on_render(SDL_Renderer *renderer) {
}

void StartMenu::on_event(SDL_Event *event) {
}

