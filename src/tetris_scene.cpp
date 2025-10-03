#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>
#include <cmath>
#include "../include/scenemanager.h"
#include "../include/tetris_scene.h"
//#include "../include/menu.h"
#include "../include/scene.h"
#include "../include/button.h"
#include "../include/constants.h"
#include "../include/tetris_display.h"
#include "../include/tetris.h"

Termino terminomino;

// constructor
TetrisScene::TetrisScene() : Scene("Tetris") {
  init();
}
TetrisScene::~TetrisScene() {}

void back() {
  //SceneManager::getInstance().transition(std::make_unique<StartMenu>());
  SceneManager::getInstance().return_scene();
}

void TetrisScene::init() {
  const float centerX = constants::SCREEN_WIDTH / 2.0;
  const float centerY = constants::SCREEN_HEIGHT / 2.0;

  Button *btnBack = new Button(10, 10, 50, 50, &back);
  push_obj(btnBack);

  //push_obj(new TetrisDisplay(constants::TETRIS_X, constants::TETRIS_Y, constants::TETRIS_WIDTH));
}


Uint64 start_time = SDL_GetTicks();
int level = 5;
void TetrisScene::on_render(SDL_Renderer *renderer) {
  SDL_RenderLine(renderer, 0, 0, 50, 50);

  terminomino.render(renderer);
  //drop down speed

  // === game logic ===
  Uint64 end = SDL_GetTicks();

  // *1000 to get time in miliseconds
  float time = std::pow(0.8-(level-1)*0.007, level-1) * 1000;
  if (end > start_time + time) {
    start_time = SDL_GetTicks();

    terminomino.move_down();
  }
}

void TetrisScene::on_event(SDL_Event *event) {
  if (event->type == SDL_EVENT_KEY_DOWN) {
    if (event->key.key == SDLK_LEFT) {
      terminomino.move(-1, 0);
    }
    if (event->key.key == SDLK_RIGHT) {
      terminomino.move(1, 0);
    }
    if (event->key.key == SDLK_Z) {
      terminomino.rotate_left();
    }
    if (event->key.key == SDLK_X) {
      terminomino.rotate_right();
    }
    if (event->key.key == SDLK_SPACE) {
      terminomino.quick_place();
    }
  }
}

