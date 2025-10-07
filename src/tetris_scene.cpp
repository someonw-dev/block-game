#include <SDL3/SDL_blendmode.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>
#include <cmath>
#include <cstring>
#include <string>
#include "../include/scenemanager.h"
#include "../include/tetris_scene.h"
//#include "../include/menu.h"
#include "../include/scene.h"
#include "../include/button.h"
#include "../include/constants.h"
#include "../include/tetris.h"
#include "../include/text.h"

Tetris terminomino;
static bool paused = false;

// constructor
TetrisScene::TetrisScene() : Scene("Tetris") {
  init();
}
TetrisScene::~TetrisScene() {}

void resume() {
  paused = false;
}

void paused_game() {
  paused = true;
}

void return_button() {
  // should take you to the level select
  //SceneManager::getInstance().transition(std::make_unique<StartMenu>());
  SceneManager::getInstance().return_scene();
}

void quit_tetris() {
  // pushes a quit event
  SDL_Event event;
  SDL_zero(event);
  event.type = SDL_EVENT_QUIT;
  SDL_PushEvent(&event);
}

Text *score;

void TetrisScene::init() {
  const float centerX = constants::SCREEN_WIDTH / 2.0;
  const float centerY = constants::SCREEN_HEIGHT / 2.0;

  Button *btnPause= new Button(constants::SCREEN_WIDTH - 50, 10, 40, 40, &paused_game);
  btnPause->set_text(std::make_unique<Text>("||", 0, 0, 15, SceneManager::getInstance().get_renderer()));
  push_obj(btnPause);

  //push_obj(new TetrisDisplay(constants::TETRIS_X, constants::TETRIS_Y, constants::TETRIS_WIDTH));

  score = new Text("Score: 0", constants::TETRIS_X +constants::TETRIS_WIDTH + 10, 100, 100, SceneManager::getInstance().get_renderer());
  push_obj(score);

  const float WIDTH = 150;
  const float HEIGHT = 60;
  const float BUTTON_CENTER = centerX - WIDTH * 0.5;

  Text *lblPaused = new Text("Paused", centerX - 100, 30, 200, SceneManager::getInstance().get_renderer());
  push_paused_object(lblPaused);

  Button *btnContinue= new Button(BUTTON_CENTER, centerY - 50 , WIDTH, HEIGHT, &resume);
  btnContinue->set_text(std::make_unique<Text>("Continue", 0, 0, 100, SceneManager::getInstance().get_renderer()));
  push_paused_object(btnContinue);

  Button *btnBack = new Button(BUTTON_CENTER, centerY + 50, WIDTH, HEIGHT, &return_button);
  btnBack->set_text(std::make_unique<Text>("Back", 0, 0, 60, SceneManager::getInstance().get_renderer()));
  push_paused_object(btnBack);

  /*
  Button *btnExit= new Button(BUTTON_CENTER, centerY + 150, WIDTH, HEIGHT, &quit_tetris);
  btnExit->set_text(std::make_unique<Text>("Quit", 0, 0, 50, SceneManager::getInstance().get_renderer()));
  push_paused_object(btnExit);
  */
}


void TetrisScene::on_render(SDL_Renderer *renderer) {
  //SDL_RenderLine(renderer, 0, 0, 50, 50);

  score->update_text(terminomino.get_score(), renderer);
  terminomino.render(renderer);

  if (paused) {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_FRect rect {0, 0, constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 100);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    for (Object *i : paused_objects) {
      i->render(renderer);
    }
  }
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

    if (!paused) {
      terminomino.move_down();
    }
  }
}

void TetrisScene::on_event(SDL_Event *event) {
  // TODO: write this in update so that the presses feel better
  if (event->type == SDL_EVENT_KEY_DOWN) {
    if (!paused) {
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
    if (event->key.scancode == SDL_SCANCODE_ESCAPE) {
      paused = !paused;
    }
    if (paused) {
    }
  }

  if (paused) {
    for (Object *i : paused_objects) {
      i->on_event(event);
    }
  }
}

