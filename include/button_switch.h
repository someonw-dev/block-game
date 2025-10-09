#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <iterator>
#include <memory>
#include "object.h"
#include "text.h"

class ButtonSwitch : public Object
{
public:
  //Bjarne Stroustrup the inventor of C++ suggests to use public first and then private.
  // ==== Constructor ====
  ButtonSwitch(float x, float y, float width, float height, void(*callbackFunc)()) : Object(x, y, width, height){
    inner = {x + BORDER, y + BORDER, width - BORDER*2, height-BORDER*2};

    int inner_x = x + BORDER;
    int inner_y = y + BORDER;

    float size_mod;
    if (width > height) {
      size_mod = width * 0.05;
    } else {
      size_mod = height * 0.05;
    }
    const float SHADOW_LENGTH = size_mod;
    shadow_bottom.w = width - BORDER*2;
    shadow_bottom.x = inner_x;
    shadow_bottom.y = y + height - SHADOW_LENGTH - BORDER;
    shadow_bottom.h = SHADOW_LENGTH;

    shadow_right.w = SHADOW_LENGTH;
    shadow_right.x = x + width - SHADOW_LENGTH - BORDER;
    shadow_right.y = inner_y;
    shadow_right.h = height - BORDER * 2;

    const float HIGHLIGHT_LENGTH = size_mod;

    highlight[0].x = inner_x;
    highlight[0].y = inner_y;
    highlight[0].w = HIGHLIGHT_LENGTH * 5;
    highlight[0].h = HIGHLIGHT_LENGTH;
    highlight[1].y = inner_y;
    highlight[1].x = inner_x;
    highlight[1].w = HIGHLIGHT_LENGTH;
    highlight[1].h = HIGHLIGHT_LENGTH * 3;

    callback = callbackFunc;
  }
  ~ButtonSwitch() {};

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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &region);

    main_colour(renderer);
    SDL_RenderFillRect(renderer, &inner);

    shadow_colour(renderer);
    SDL_RenderFillRect(renderer, &shadow_bottom);
    SDL_RenderFillRect(renderer, &shadow_right);

    highlight_colour(renderer);
    for (SDL_FRect &i: highlight) {
      SDL_RenderFillRect(renderer, &i);
    }

    if (enabled) {
      if (enabled_text) {
        enabled_text->render(renderer);
      }
    } else {
      if (disabled_text) {
        disabled_text->render(renderer);
      }
    }
  }

  void set_enabled_text_text(std::unique_ptr<Text> text) {
    enabled_text = std::move(text);
    enabled_text->set_x(region.x + region.w * 0.5 - enabled_text->get_width() * 0.5);
    enabled_text->set_y(region.y + region.h * 0.5 - enabled_text->get_height() * 0.5);
  }

  void set_disabled_text_text(std::unique_ptr<Text> text) {
    disabled_text = std::move(text);
    disabled_text->set_x(region.x + region.w * 0.5 - disabled_text->get_width() * 0.5);
    disabled_text->set_y(region.y + region.h * 0.5 - disabled_text->get_height() * 0.5);
  }

  void change_state(bool new_state) {
    enabled = new_state;
  }

  bool get_state() {
    return enabled;
  }

private:
  bool hover;
  bool enabled;
  const int BORDER = 5;
  void(*callback)();
  std::unique_ptr<Text> enabled_text = nullptr;
  std::unique_ptr<Text> disabled_text = nullptr;
  SDL_FRect shadow_bottom;
  SDL_FRect shadow_right;
  SDL_FRect inner;
  SDL_FRect highlight[2];

  bool in_button(SDL_FPoint cursor) {
    if (SDL_PointInRectFloat(&cursor, &region)) {
      return true;
    } else {

      return false;
    }
  }

  void main_colour(SDL_Renderer *renderer) {
    if (enabled) {
      if (hover == true) {
        SDL_SetRenderDrawColor(renderer, 126, 225, 0, 255);
      } else {
        SDL_SetRenderDrawColor(renderer, 183, 255, 0, 255);
      }
    } else {
      if (hover == true) {
        SDL_SetRenderDrawColor(renderer, 240, 0, 0, 255);
      } else {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
      }
    }
  }

  void shadow_colour(SDL_Renderer *renderer) {
    if (enabled) {
      if (hover == true) {
        SDL_SetRenderDrawColor(renderer, 71, 160, 0, 255);
      } else {
        SDL_SetRenderDrawColor(renderer, 70, 185, 0, 255);
      }
    } else {
      if (hover == true) {
        SDL_SetRenderDrawColor(renderer, 150, 0, 0, 255);
      } else {
        SDL_SetRenderDrawColor(renderer, 185, 0, 0, 255);
      }
    }
  }

  void highlight_colour(SDL_Renderer *renderer) {
    if (hover == true) {
      SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    } else {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }
  }
};
