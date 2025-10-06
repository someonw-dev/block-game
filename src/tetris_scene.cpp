#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>
#include <cmath>
#include "../include/scenemanager.h"
#include "../include/tetris_scene.h"
//#include "../include/menu.h"
#include "../include/scene.h"
#include "../include/button.h"
#include "../include/constants.h"
#include "../include/tetris.h"
#include "../include/text.h"

Tetris terminomino;

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


  Text *title = new Text("test", 100, 100, 100, SceneManager::getInstance().get_renderer());
  push_obj(title);
}


void TetrisScene::on_render(SDL_Renderer *renderer) {
  //SDL_RenderLine(renderer, 0, 0, 50, 50);

  terminomino.render(renderer);
}

void TetrisScene::update() {
  const bool* keys = SDL_GetKeyboardState(NULL);

  static Uint64 start_time = SDL_GetTicks();
  static int level = 5;

  // TODO: on down arrow reset timer also if next down move will place the tile and you move gives you a little extra time
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
  // TODO: write this in update so that the presses feel better
  if (event->type == SDL_EVENT_KEY_DOWN) {
    if (event->key.scancode == SDL_SCANCODE_LEFT) {
      terminomino.move(-1, 0);
    }
    if (event->key.scancode == SDL_SCANCODE_RIGHT) {
      terminomino.move(1, 0);
    }
    if (event->key.scancode == SDL_SCANCODE_DOWN) {
      terminomino.move(0, -1);
    }
    if (event->key.scancode == SDL_SCANCODE_Z) {
      terminomino.rotate_left();
    }
    if (event->key.scancode == SDL_SCANCODE_X) {
      terminomino.rotate_right();
    }
    if (event->key.scancode == SDL_SCANCODE_SPACE) {
      terminomino.quick_place();
    }
    if (event->key.scancode == SDL_SCANCODE_C) {
      terminomino.swap_active_piece();
    }
  }
}

