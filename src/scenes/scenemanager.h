#pragma once

#include "scene.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <memory>
#include <utility>

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
  void transition(std::unique_ptr<Scene> to) {
    // keeps the old scene in memory or else there will be some
    // race condition errors also allows you to essentiatly save a scene state since it isnt unloaded by memory
    // its kinda iffy though ill have to maybe come back to this later
    oldScene = std::move(currentScene);
    currentScene = std::move(to);
    //currentScene->on_resize(window);
  }

  void return_scene() {
    std::unique_ptr<Scene> temp = std::move(currentScene);
    currentScene = std::move(oldScene);
    oldScene = std::move(temp);
  }

  void render(SDL_Renderer *renderer) {
    if (currentScene) {
      currentScene->render_handler(renderer);
    }
  }

  void update(SDL_Event *event) {
    if (currentScene) {
      currentScene->event_handler(event);
    }
  }

  void quit() {
    SDL_Quit();
  }

private:
  // this is also for the singleton pattern
  SceneManager() {};

  // at first i didnt use a smart pointer but memory management was a bit concerning
  std::unique_ptr<Scene> oldScene = nullptr;
  std::unique_ptr<Scene> currentScene = nullptr;
};
