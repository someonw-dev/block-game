// header gaurd
#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <memory>
#include "object.h"
#include "text.h"

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
    if (caption) {
      caption->render(renderer);
    }
  }

  void set_text(std::unique_ptr<Text> text) {
    caption = std::move(text);
    caption->set_x(region.x + region.w * 0.5 - caption->get_width() * 0.5);
    caption->set_y(region.y + region.h * 0.5 - caption->get_height() * 0.5);
  }


private:
  bool hover;
  void(*callback)();
  std::unique_ptr<Text> caption = nullptr;

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
