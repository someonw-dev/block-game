#include <memory>
#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include "scenemanager.h"
#include "scene.h"
#include "menu.h"

static SDL_Window *window = nullptr;
static SDL_Renderer *renderer = nullptr;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
  if (!SDL_Init(SDL_INIT_VIDEO)) 
  {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  if (!SDL_CreateWindowAndRenderer("Scene Window!", 500, 300, SDL_WINDOW_RESIZABLE, &window, &renderer))
  {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  SceneManager::getInstance().transition(std::make_unique<StartMenu>());

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
  if (event->type == SDL_EVENT_QUIT)
  {
    return SDL_APP_SUCCESS;
  } else {
    SceneManager::getInstance().update(event);
  }

  //SDL_EVENT_WINDOW_RESIZED

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  SceneManager::getInstance().render(renderer);

  SDL_RenderPresent(renderer);

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
  // Exits the program and ensures there isnt anything left
}
