#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>
#include <cmath>
#include "scenemanager.h"
#include "tetris_scene.h"
#include "menu.h"
#include "scene.h"
#include "../components/button.h"
#include "../constants.h"
#include "../components/tetris_cube.h"

// constructor
TetrisScene::TetrisScene() : Scene("Menu") {
  init();
}
TetrisScene::~TetrisScene() {}

void back() {
  std::cout << "play" << std::endl;
  //SceneManager::getInstance().transition(std::make_unique<StartMenu>());
  SceneManager::getInstance().return_scene();
}

void TetrisScene::init() {
  const float centerX = constants::SCREEN_WIDTH / 2.0;
  const float centerY = constants::SCREEN_HEIGHT / 2.0;

  const float width = 200;
  const float height = 100;

  Button *btnBack = new Button(10, 10, 50, 50, &back);
  push_obj(btnBack);
  push_obj(new Cube(100, 100, 50));
}


Uint64 start_time = SDL_GetTicks();
int level = 1;
void TetrisScene::on_render(SDL_Renderer *renderer) {
  SDL_RenderLine(renderer, 0, 0, 50, 50);
  
  //drop down speed

  // === game logic ===
  Uint64 end = SDL_GetTicks();

  // *1000 to get time in miliseconds
  float time = std::pow(0.8-(level-1)*0.007, level-1) * 1000;
  if (end > start_time + time) {

    start_time = SDL_GetTicks();
    //move block down
    std::cout << "down" << std::endl;
  }
}

void TetrisScene::on_event(SDL_Event *event) {
}

