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
static bool first_session = false;

// constructor
TetrisScene::TetrisScene() : Scene("Tetris") {
  init();
}

TetrisScene::~TetrisScene() {
    for (Object *i : paused_objects) {
      delete i;
  }
    for (Object *i : lost_objects) {
      delete i;
  }
}

void start_game() {
  terminomino.start();
}

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

Text *score;
Text *level;

void TetrisScene::init() {
  const float centerX = constants::SCREEN_WIDTH / 2.0;
  const float centerY = constants::SCREEN_HEIGHT / 2.0;

  Button *btnPause= new Button(constants::SCREEN_WIDTH - 50, 10, 40, 40, &paused_game);
  btnPause->set_text(std::make_unique<Text>("||", 0, 0, 15, SceneManager::getInstance().get_renderer()));
  push_obj(btnPause);

  //push_obj(new TetrisDisplay(constants::TETRIS_X, constants::TETRIS_Y, constants::TETRIS_WIDTH));

  const float TETRIS_RIGHT = constants::TETRIS_X + constants::TETRIS_WIDTH;
  const float RIGHT_MARGIN = 20;

  score = new Text("Score: 0", TETRIS_RIGHT + RIGHT_MARGIN, 230, 140, SceneManager::getInstance().get_renderer());
  push_obj(score);

  level = new Text("Level: 1", TETRIS_RIGHT + RIGHT_MARGIN, 270, 80, SceneManager::getInstance().get_renderer());
  push_obj(level);
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

  Button *btnRestart = new Button(TETRIS_RIGHT + RIGHT_MARGIN, centerY + 50, 100, 40, &start_game);
  btnRestart->set_text(std::make_unique<Text>("Start", 0, 0, 60, SceneManager::getInstance().get_renderer()));
  push_lost_object(btnRestart);
  /*
  Button *btnExit= new Button(BUTTON_CENTER, centerY + 150, WIDTH, HEIGHT, &quit_tetris);
  btnExit->set_text(std::make_unique<Text>("Quit", 0, 0, 50, SceneManager::getInstance().get_renderer()));
  push_paused_object(btnExit);
  */
}


void TetrisScene::on_render(SDL_Renderer *renderer) {
  //SDL_RenderLine(renderer, 0, 0, 50, 50);

  static int score_value;

  // only update the text if it has changed since this can be a little expensive
  if (score_value != terminomino.get_score()) {
    score_value = terminomino.get_score();
    static char str[100];
    strcpy(str, "Score: ");
    strcat(str, std::to_string(score_value).c_str());
    score->update_text(str, renderer);
  }
  terminomino.render(renderer);


  if (!terminomino.is_running()) {
    for (Object *i : lost_objects) {
      i->render(renderer);
    }
  }

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

  static Uint64 start_time = SDL_GetTicks();
  int level = terminomino.get_level();

  // =======================
  // ======== input ========
  // =======================

  const bool* keys = SDL_GetKeyboardState(NULL);





  // === game logic ===
  Uint64 end = SDL_GetTicks();

  // *1000 to get time in miliseconds
  float time = std::pow(0.8-(level-1)*0.007, level-1) * 1000;

  // on left/right/rotate if it is next_fall_place do the mercy period
  // on down, quick_place, swap active piece reset start_time

  if (end > start_time + time) {
    start_time = SDL_GetTicks();

    if (!paused && terminomino.is_running()) {
      terminomino.fall();
    }
  }
}

void TetrisScene::on_event(SDL_Event *event) {
  // TODO: write this in update so that the presses feel better
  if (event->type == SDL_EVENT_KEY_DOWN) {
    if (!paused && terminomino.is_running()) {
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
  }

  if (!terminomino.is_running() && !paused) {
    for (Object *i : lost_objects) {
      i->on_event(event);
    }
  }

  if (paused) {
    for (Object *i : paused_objects) {
      i->on_event(event);
    }
  }
}

