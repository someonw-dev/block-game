#include "../include/highscore_scene.h"
#include "../include/button.h"
#include "../include/constants.h"
#include "../include/scenemanager.h"
#include "../include/background.h"

HighscoreScene::HighscoreScene() : Scene("Menu") {
  init();
}
HighscoreScene::~HighscoreScene() {}

void return_event() {
  SceneManager::getInstance().return_scene();
}

void HighscoreScene::init() {
  Background *background = new Background();
  push_obj(background);

  const float centerX = constants::SCREEN_WIDTH / 2.0;
  const float centerY = constants::SCREEN_HEIGHT / 2.0;

  const float WIDTH = 150;
  const float HEIGHT = 60;
  const float BUTTON_CENTER = centerX - WIDTH * 0.5;

  Button *btnReturn = new Button(BUTTON_CENTER, centerY - 50, WIDTH, HEIGHT, &return_event);
  btnReturn->set_text(std::make_unique<Text>("RETURN", 0, 0, 65, SceneManager::getInstance().get_renderer()));
  push_obj(btnReturn);
}

void HighscoreScene::on_render(SDL_Renderer *renderer) {
}

void HighscoreScene::on_event(SDL_Event *event) {
}

