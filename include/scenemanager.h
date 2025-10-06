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
    // this does always keep the old scene in memory which i want for certain scenes
    // but not all of them so i'll come back to this later and add an actual save state and whatnot
    // TODO: rewrite this to only save scenes when necesarry
    // in rendering
    // if (newScene) {
    //  oldScene = std::move(newScene)
    // }

    oldScene = std::move(currentScene);
    currentScene = std::move(to);
  }

  void return_scene() {
    std::unique_ptr<Scene> temp = std::move(currentScene);
    currentScene = std::move(oldScene);
    oldScene = std::move(temp);
  }

  void render() {
    if (currentScene) {
      currentScene->render_handler(renderer);
    }
  }

  void update(SDL_Event *event) {
    if (currentScene) {
      currentScene->event_handler(event);
    }
  }

  void set_renderer(SDL_Renderer *set_renderer) {
    renderer = set_renderer;
  }

  SDL_Renderer* get_renderer() {
    return renderer;
  }

  void quit() {
    SDL_Quit();
  }

private:
  // this is also for the singleton pattern
  SceneManager() {};

  // smart pointer for memory management
  std::unique_ptr<Scene> oldScene = nullptr;
  std::unique_ptr<Scene> currentScene = nullptr;
  SDL_Renderer *renderer;
};
