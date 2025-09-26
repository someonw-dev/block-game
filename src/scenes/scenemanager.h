#pragma once

#include "scene.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <memory>

// singleton type obj
// https://stackoverflow.com/questions/1008019/how-do-you-implement-the-singleton-design-pattern

class SceneManager {
public:
  // ===========================
  // ==== Singleton pattern ====

  static SceneManager& getInstance()
  {
    static SceneManager instance; // Guaranteed to be destroyed.
    // Instantiated on first use.
    return instance;
  }

  SceneManager(SceneManager const&) = delete;
  void operator=(SceneManager const&) = delete;

  // ==== Singleton pattern ====
  // ===========================

  // TODO: add some way to transition while keeping the scene condition
  void transition(std::shared_ptr<Scene> to) {

    currentScene = std::move(to);
    //currentScene->on_resize(window);
  }

  void render(SDL_Renderer *renderer) {
    if (currentScene) {
      currentScene->render(renderer);
    }
  }

  void update(SDL_Event *event) {
    if (currentScene) {
      currentScene->on_event(event);
    }
  }

  // width and height of the window
  void on_resize(int w, int h) {
    if (currentScene) {
      currentScene->on_resize(w, h);
    }
  }

private:
  // this is also for the singleton pattern
  SceneManager() {};

  // at first i didnt use a smart pointer but memory management was starting to concern me...
  std::shared_ptr<Scene> currentScene = nullptr;
  SDL_Window *window;

};
