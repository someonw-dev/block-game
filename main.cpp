#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_timer.h>
#include <cstdlib>
#include <ctime>
#define SDL_MAIN_USE_CALLBACKS 1

//#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <math.h>
#include <SDL3/SDL_hints.h>
#include "include/scenemanager.h"
#include "include/menu.h"
#include "include/constants.h"

int width = constants::SCREEN_WIDTH;
int height = constants::SCREEN_HEIGHT;

static SDL_Window *window = nullptr;
static SDL_Renderer *renderer = nullptr;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
  if (!SDL_Init(SDL_INIT_VIDEO)) 
  {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  if (!SDL_CreateWindowAndRenderer("Scene Window!", width, height, SDL_WINDOW_RESIZABLE, &window, &renderer))
  {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  SDL_GetWindowSize(window, &width, &height);
  //SDL_SetRenderLogicalPresentation(renderer, 1000, 500, SDL_LOGICAL_PRESENTATION_LETTERBOX);
  SceneManager::getInstance().transition(std::make_unique<StartMenu>());
  if (!SDL_SetHint(SDL_HINT_MAIN_CALLBACK_RATE, "60")) {
    SDL_Log("Couldn't change callback rate: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  srand(time(NULL));

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
  if (event->type == SDL_EVENT_QUIT)
  {
    return SDL_APP_SUCCESS;
  } else  if (event->type == SDL_EVENT_WINDOW_RESIZED){
    int newWidth = 0;
    int newHeight = 0;

    SDL_GetWindowSize(window, &newWidth, &newHeight);

    float ratioX = newWidth*1.0 / width;
    float ratioY = newHeight*1.0 / height;

    // spent an dumb amount of time trying to make resizing work but this just works
    SDL_SetRenderScale(renderer, ratioX, ratioY);
  } else {
    // you need this function so your mouse coordinates update to the new resolutions
    SDL_ConvertEventToRenderCoordinates(renderer, event);
    SceneManager::getInstance().update(event);
  }

  //SDL_EVENT_WINDOW_RESIZED

  return SDL_APP_CONTINUE;
}
int frames = 0;
Uint64 start = 0;
SDL_AppResult SDL_AppIterate(void *appstate)
{

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  SceneManager::getInstance().render(renderer);

  SDL_RenderPresent(renderer);

  Uint64 end = SDL_GetTicks();
  ++frames;

  if (end > start + 1000) {

    start = SDL_GetTicks();
    //std::cout << "Current FPS: " << std::to_string(frames) << std::endl;
    frames = 0;
  }

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
  // Exits the program and ensures there isnt anything left
}
