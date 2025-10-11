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
#include "../include/input.h"
#include "../include/button_switch.h"
#include "../include/background.h"
#include "../include/menu.h"
#include "../include/highscore_scene.h"

// having the piece defined here lets it stay alive even when the scene gets killed
Tetris terminomino;
static bool paused = false;
static bool first_session = true;
static int start_level = 1;
ButtonSwitch *btnInfinity;

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
  for (Object *i : shared_objects) {
    delete i;
  }
  for (Object *i : first_objects) {
    delete i;
  }
}

void start_game() {
  first_session = false;
  terminomino.start(start_level);
}

void resume() {
  paused = false;
}

void paused_game() {
  paused = true;
}

void return_button() {
  // should take you to the menu
  SceneManager::getInstance().transition(std::make_unique<StartMenu>());
}

void change_infinity() {
  terminomino.change_infinity_permissions();
  btnInfinity->change_state(terminomino.get_infinity_permissions());
}


void tetris_to_highscore() {
  SceneManager::getInstance().transition(std::make_unique<HighscoreScene>());
}

void TetrisScene::pause_init() {
  const float centerX = constants::SCREEN_WIDTH / 2.0;
  const float centerY = constants::SCREEN_HEIGHT / 2.0;
  const float TETRIS_RIGHT = constants::TETRIS_X + constants::TETRIS_WIDTH;
  const float RIGHT_MARGIN = 20;
  const float WIDTH = 150;
  const float HEIGHT = 50;
  const float BUTTON_CENTER = centerX - WIDTH * 0.5;

  Text *lblPaused = new Text("Paused", centerX - 100, centerY - 130, 200, SceneManager::getInstance().get_renderer());
  push_paused_object(lblPaused);

  Button *btnContinue= new Button(BUTTON_CENTER, centerY - 60 , WIDTH, HEIGHT, &resume);
  btnContinue->set_text(std::make_unique<Text>("Continue", 0, 0, 100, SceneManager::getInstance().get_renderer()));
  push_paused_object(btnContinue);

  Button *btnHighscores = new Button(BUTTON_CENTER, centerY + 5, WIDTH, HEIGHT, &tetris_to_highscore);
  btnHighscores->set_text(std::make_unique<Text>("HIGHSCORES", 0, 0, 130, SceneManager::getInstance().get_renderer()));
  push_paused_object(btnHighscores);

  Button *btnBack = new Button(BUTTON_CENTER, centerY + 70, WIDTH, HEIGHT, &return_button);
  btnBack->set_text(std::make_unique<Text>("Menu", 0, 0, 60, SceneManager::getInstance().get_renderer()));
  push_paused_object(btnBack);

  const float INFINITY_X = BUTTON_CENTER - 150;
  Text *lblInfinity= new Text("Infinity", INFINITY_X + 15, centerY - 30, 100, SceneManager::getInstance().get_renderer());
  push_paused_object(lblInfinity);

  btnInfinity = new ButtonSwitch(INFINITY_X, centerY, WIDTH - 20, HEIGHT - 10, &change_infinity);
  btnInfinity->set_enabled_text_text(std::make_unique<Text>("Enabled", 0, 0, 80, SceneManager::getInstance().get_renderer()));
  btnInfinity->set_disabled_text_text(std::make_unique<Text>("Disabled", 0, 0, 80, SceneManager::getInstance().get_renderer()));
  btnInfinity->change_state(terminomino.get_infinity_permissions());
  push_paused_object(btnInfinity);


}

void TetrisScene::shared_init() {
  const float centerX = constants::SCREEN_WIDTH / 2.0;
  const float centerY = constants::SCREEN_HEIGHT / 2.0;

  const float TETRIS_RIGHT = constants::TETRIS_X + constants::TETRIS_WIDTH;
  const float RIGHT_MARGIN = 20;

  Button *btnRestart = new Button(TETRIS_RIGHT + RIGHT_MARGIN, centerY + 50, 100, 40, &start_game);
  btnRestart->set_text(std::make_unique<Text>("Start", 0, 0, 60, SceneManager::getInstance().get_renderer()));
  push_shared_object(btnRestart);
}

void TetrisScene::lost_init() {

}

void TetrisScene::init() {
  Background *background = new Background();
  push_obj(background);

  const float centerX = constants::SCREEN_WIDTH / 2.0;
  const float centerY = constants::SCREEN_HEIGHT / 2.0;

  const float TETRIS_RIGHT = constants::TETRIS_X + constants::TETRIS_WIDTH;
  const float RIGHT_MARGIN = 20;

  Button *btnPause= new Button(constants::SCREEN_WIDTH - 50, 10, 40, 40, &paused_game);
  btnPause->set_text(std::make_unique<Text>("||", 0, 0, 15, SceneManager::getInstance().get_renderer()));
  push_obj(btnPause);

  const float LABEL_START_Y = 300;

  score = new Text("Score: 0", TETRIS_RIGHT + RIGHT_MARGIN, LABEL_START_Y, 140, SceneManager::getInstance().get_renderer());
  push_obj(score);

  level = new Text("Level: 1", TETRIS_RIGHT + RIGHT_MARGIN, LABEL_START_Y + 30, 80, SceneManager::getInstance().get_renderer());
  push_obj(level);

  lines_needed = new Text("Lines: 10", TETRIS_RIGHT + RIGHT_MARGIN, LABEL_START_Y + 47, 90, SceneManager::getInstance().get_renderer());
  push_obj(lines_needed);

  pause_init();
  shared_init();
}

void update_text(int old_value, int value, const char label[], Text *text, SDL_Renderer *renderer) {
  // only update the text if it has changed since this can be a little expensive
  if (old_value != value) {
    old_value = value;
    static char str[100];
    strcpy(str, label);
    strcat(str, std::to_string(old_value).c_str());
    text->update_text(str, renderer);
  }
}

void TetrisScene::on_render(SDL_Renderer *renderer) {
  //SDL_RenderLine(renderer, 0, 0, 50, 50);

  static int score_value = 0;
  static int level_value = 1;
  static int lines_needed_value = 10;

  update_text(score_value, terminomino.get_score(), "Score: ", score, renderer);
  update_text(level_value, terminomino.get_level(), "Level: ", level, renderer);
  update_text(lines_needed_value, terminomino.get_lines_needed(), "Lines: ", lines_needed, renderer);

  terminomino.render(renderer);

  if (!terminomino.is_running() || first_session) {
    for (Object *i : shared_objects) {
      i->render(renderer);
    }
  }

  if (paused) {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    static SDL_FRect pause_gray {0, 0, constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 100);
    SDL_RenderFillRect(renderer, &pause_gray);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    static const float PAUSE_WIDTH = 500;
    static const float PAUSE_HEIGHT = 300;
    static const float MENU_X = constants::SCREEN_WIDTH * 0.5 - PAUSE_WIDTH *0.5;
    static const float MENU_Y = constants::SCREEN_HEIGHT * 0.5 - PAUSE_HEIGHT*0.5;
    static SDL_FRect pause_menu {MENU_X, 200, PAUSE_WIDTH, 300};
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderFillRect(renderer, &pause_menu);

    for (Object *i : paused_objects) {
      i->render(renderer);
    }
  }
}

void TetrisScene::update() {

  static Uint64 start_time = SDL_GetTicks();
  int level = terminomino.get_level();

  Uint64 end = SDL_GetTicks();

  // *1000 to get time in miliseconds
  float time = std::pow(0.8-(level-1)*0.007, level-1) * 1000;

  // =======================
  // ======== input ========
  // =======================
  static InputHandler down = {SDL_SCANCODE_DOWN};
  static InputHandler left = {SDL_SCANCODE_LEFT};
  static InputHandler right = {SDL_SCANCODE_RIGHT};
  static InputHandler rotate_right = {SDL_SCANCODE_X};
  static InputHandler rotate_left = {SDL_SCANCODE_Z};

  const bool* keys = SDL_GetKeyboardState(NULL);

  if (!paused && terminomino.is_running()) {
    if (down.get_pressed(keys)) {
      if (terminomino.move_down()) {
        start_time = SDL_GetTicks();
      }
    }
    if (left.get_pressed(keys)) {
      // should only infinity if your move actually goes through
      if (terminomino.move(-1, 0) && terminomino.can_infinity()) {
          start_time = SDL_GetTicks();
      }
    }
    if (right.get_pressed(keys)) {
      if (terminomino.move(1, 0) && terminomino.can_infinity()) {
        start_time = SDL_GetTicks();
      }
    }
    if (rotate_left.get_pressed(keys)) {
      if (terminomino.rotate_left() && terminomino.can_infinity()) {
        start_time = SDL_GetTicks();
      }
    }
    if (rotate_right.get_pressed(keys)) {
      if (terminomino.rotate_right() && terminomino.can_infinity()) {
        start_time = SDL_GetTicks();
      }
    }
  }

  if (terminomino.is_running()) {
    if (terminomino.next_fall_is_place()) {
      time = 500;
    }
  }

  // === game logic ===

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
      // these can be here since they are 1 button inputs anyways
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

  if ((!terminomino.is_running() || first_session) && !paused) {
    for (Object *i : shared_objects) {
      i->on_event(event);
    }
  }

  if (paused) {
    for (Object *i : paused_objects) {
      i->on_event(event);
    }
  }
}

