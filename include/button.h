// header gaurd
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

class Button : public Object
{
public:
  //Bjarne Stroustrup the inventor of C++ suggests to use public first and then private.
  // ==== Constructor ====
  Button(float x, float y, float width, float height, void(*callbackFunc)()) : Object(x, y, width, height){
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
    highlight[2].x = highlight[0].x + width ;
    highlight[2].y = highlight[1].y;

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
  const int BORDER = 5;
  void(*callback)();
  std::unique_ptr<Text> caption = nullptr;
  SDL_FRect shadow_bottom;
  SDL_FRect shadow_right;
  SDL_FRect inner;
  SDL_FRect highlight[3];

  bool in_button(SDL_FPoint cursor) {
    if (SDL_PointInRectFloat(&cursor, &region)) {
      return true;
    } else {

      return false;
    }
  }

  void main_colour(SDL_Renderer *renderer) {
    if (hover == true) {
      SDL_SetRenderDrawColor(renderer, 0, 216, 189, 255);
    } else {
      SDL_SetRenderDrawColor(renderer, 0, 255, 223, 255);
    }
  }

  void shadow_colour(SDL_Renderer *renderer) {
    if (hover == true) {
      SDL_SetRenderDrawColor(renderer, 0, 118, 103, 255);
    } else {
      SDL_SetRenderDrawColor(renderer, 0, 159, 139, 255);
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
