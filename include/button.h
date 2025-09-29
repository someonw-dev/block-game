// header gaurd
#pragma once

#include "object.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <iostream>

class Button : public Object
{
public:
  //Bjarne Stroustrup the inventor of C++ suggests to use public first and then private.
  // ==== Constructor ====
  Button(float x, float y, float width, float height, void(*callbackFunc)()) : Object(x, y, width, height){
    callback = callbackFunc;
  }
  Button(float x, float y, float width, float height, int z, void(*callbackFunc)()) : Object(x, y, width, height, z){
    callback = callbackFunc;
  }
  ~Button() {};

  void on_event(SDL_Event *event) {
    const SDL_FPoint cursor = {event->button.x, event->button.y};

    if (in_button(cursor)) {
      hover = true;
      if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        callback();
      }
    } else {
      hover = false;
    }
  }

  void render(SDL_Renderer *renderer) {
    renderColour(renderer);
    SDL_RenderFillRect(renderer, &region);
  }


private:
  bool hover;
  void(*callback)();

  bool in_button(SDL_FPoint cursor) {
    if (SDL_PointInRectFloat(&cursor, &region)) {
      return true;
    } else {
      return false;
    }
  }

  void renderColour(SDL_Renderer *renderer) {
    if (hover == true) {
      SDL_SetRenderDrawColor(renderer, 5, 30, 220, 255);
    } else {
      SDL_SetRenderDrawColor(renderer, 10, 50, 250, 255);
    }
  }

};
