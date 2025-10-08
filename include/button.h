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
    const int SHADOW_BOTTOM_HEIGHT = 6;
    shadow_bottom.w = width;
    shadow_bottom.x = x;
    shadow_bottom.y = y + height - SHADOW_BOTTOM_HEIGHT;
    shadow_bottom.h = SHADOW_BOTTOM_HEIGHT;

    const int SHADOW_RIGHT_WIDTH = 4;
    shadow_right.w = SHADOW_RIGHT_WIDTH;
    shadow_right.x = x + width - SHADOW_RIGHT_WIDTH;
    shadow_right.y = y;
    shadow_right.h = height;


    const int MARGIN = 3;

    highlight[0].x = x + MARGIN;
    highlight[0].y = y + MARGIN + height * 0.8;
    highlight[1].x = highlight[0].x;
    highlight[1].y = y + MARGIN;
    highlight[2].x = highlight[0].x + width - MARGIN * 2 - SHADOW_RIGHT_WIDTH;
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
    main_colour(renderer);
    SDL_RenderFillRect(renderer, &region);

    shadow_colour(renderer);
    SDL_RenderFillRect(renderer, &shadow_bottom);
    SDL_RenderFillRect(renderer, &shadow_right);

    highlight_colour(renderer);
    SDL_RenderLines(renderer, highlight, 3);

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
  SDL_FRect shadow_bottom;
  SDL_FRect shadow_right;
  SDL_FPoint highlight[3];

  bool in_button(SDL_FPoint cursor) {
    if (SDL_PointInRectFloat(&cursor, &region)) {
      return true;
    } else {

      return false;
    }
  }

  void main_colour(SDL_Renderer *renderer) {
    if (hover == true) {
      SDL_SetRenderDrawColor(renderer, 5, 30, 220, 255);
    } else {
      SDL_SetRenderDrawColor(renderer, 10, 50, 250, 255);
    }
  }

  void shadow_colour(SDL_Renderer *renderer) {
    if (hover == true) {
      SDL_SetRenderDrawColor(renderer, 10, 10, 150, 255);
    } else {
      SDL_SetRenderDrawColor(renderer, 50, 50, 150, 255);
    }
  }

  void highlight_colour(SDL_Renderer *renderer) {
    if (hover == true) {
      SDL_SetRenderDrawColor(renderer, 50, 50, 255, 255);
    } else {
      SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255);
    }
  }
};
