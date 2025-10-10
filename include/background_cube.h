#pragma once

#include "object.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <algorithm>
#include "object.h"
#include "colours.h"

class BackgroundCube
{
public:
  BackgroundCube(float x, float y, float cube_length, int r_value, int g_value, int b_value) {
    r = r_value;
    g = g_value;
    b = b_value;
    length = cube_length;
    HIGHLIGHT_WIDTH = length * 0.05;
    outer = {x, y, length, length};
    const float inner_x = x + BORDER;
    const float inner_length = length - BORDER*2;
    inner = {inner_x, y + BORDER, inner_length, inner_length};
    highlight1 = {inner_x, y + BORDER, HIGHLIGHT_WIDTH, HIGHLIGHT_WIDTH*3};
    highlight2 = {inner_x + HIGHLIGHT_WIDTH, y + BORDER, HIGHLIGHT_WIDTH*3, HIGHLIGHT_WIDTH};
    const float inner_bottom_y = y + length;
    shadow1 = {inner_x, y + length - BORDER - HIGHLIGHT_WIDTH, inner_length, HIGHLIGHT_WIDTH};
    shadow2 = {inner_x + inner_length - HIGHLIGHT_WIDTH, y + BORDER, HIGHLIGHT_WIDTH, inner_length};
  }
  BackgroundCube(float length) {
    HIGHLIGHT_WIDTH = length * 0.05;
    outer.w = length;
    outer.h = length;
    const float inner_length = length - BORDER * 2;
    inner.w = inner_length;
    inner.h = inner_length;

    highlight1.w = HIGHLIGHT_WIDTH;
    highlight1.h = HIGHLIGHT_WIDTH*2;
    highlight2.w = HIGHLIGHT_WIDTH;
    highlight2.h = HIGHLIGHT_WIDTH;

    shadow1.w = inner_length;
    shadow1.h = HIGHLIGHT_WIDTH;
    shadow2.w = HIGHLIGHT_WIDTH;
    shadow2.h = inner_length;
  }
 ~BackgroundCube() {}

  void render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &outer);

    //SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    //SDL_RenderFillRect(renderer, &inner);

    set_render_colour(renderer, WHITE);
    SDL_RenderFillRect(renderer, &highlight1);
    SDL_RenderFillRect(renderer, &highlight2);

    //set_render_colour(renderer, DARK_GREEN);
    SDL_SetRenderDrawColor(renderer, r, std::clamp(g - 50, 0, 255), std::clamp(b - 50, 0, 255) , 255);
    SDL_RenderFillRect(renderer, &shadow1);
    SDL_RenderFillRect(renderer, &shadow2);
  }

  void set_y(int y) {
    outer.y = y;
    inner.y = y + BORDER;
    highlight1.y = y + BORDER;
    highlight2.y = y + BORDER;
    shadow1.y = y + length - BORDER - HIGHLIGHT_WIDTH;
  }

  void set_x(int x) {
    outer.x = x;
    inner.x = x + BORDER;
    highlight1.x = x + BORDER;
    highlight2.x = x + BORDER + HIGHLIGHT_WIDTH;
  }

private:
  SDL_FRect outer;
  SDL_FRect inner;
  SDL_FRect highlight1;
  SDL_FRect highlight2;
  SDL_FRect shadow1;
  SDL_FRect shadow2;
  float HIGHLIGHT_WIDTH;
  float length;
  static const int BORDER = 3;
  int r;
  int g;
  int b;
};
