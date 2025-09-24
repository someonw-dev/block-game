#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <iostream>

// I dont need header gaurds since pragma once does that for me.
// i should get some type of function callback for button presses.
// iterator for all my buttons on screen?
class Button
{
public:
  //Bjarne Stroustrup the inventor of C++ suggests to use public first and then private.
  // ==== Constructor ====
  Button(float x, float y, float width, float height, void(*buttonPressFunc)()) {
    button_rect = {x, y, width, height};
    buttonPress = buttonPressFunc ;
  }
  ~Button() {};

  void on_event(SDL_Event *event) {
    const SDL_FPoint cursor = {event->button.x, event->button.y};

    if (inButton(cursor)) {
      hover = true;
      if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        buttonPress();
      }

    } else {
      hover = false;
    }
  }

  void render(SDL_Renderer *renderer) {
    renderColour(renderer);
    SDL_RenderFillRect(renderer, &button_rect);
  }


private:
  SDL_FRect button_rect;
  bool hover;
  void(*buttonPress)();

  bool inButton(SDL_FPoint cursor) {
    if (SDL_PointInRectFloat(&cursor, &button_rect)) {
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
