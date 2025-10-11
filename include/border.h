#pragma once
#include "object.h"
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "colours.h"

class Border : public Object
{
public:
  Border(float inner_x, float inner_y, float width, float height, float bw) : Object(0, 0, 0, 0){
    pixel_width = bw;
    cube_width = bw*3;
    inner_margin = bw*5;
    total_pixels = 14;
    left_x = inner_x - bw*total_pixels/2;
    top_y = inner_y - bw*total_pixels/2;
    border_width = width + pixel_width*total_pixels;
    border_height = width + pixel_width*total_pixels;

    border_outer.x = left_x;
    border_outer.y = top_y;
    border_outer.w = border_width;
    border_outer.h = border_height;

    background.x = left_x + pixel_width;
    background.y = top_y + pixel_width;
    background.w = border_width - pixel_width * 2;
    background.h = border_height - pixel_width * 2;

    border_inner.x = inner_x - pixel_width;
    border_inner.y = inner_y - pixel_width;
    border_inner.w = border_width - pixel_width * (total_pixels-2);
    border_inner.h = border_height - pixel_width * (total_pixels-2);

    float cube_left = left_x + pixel_width *2 + 1;
    float cube_top = top_y + pixel_width *2 + 1;
    float cube_bottom = top_y + border_height - (pixel_width *2 + 1) - cube_width;
    float cube_right = left_x + border_width - (pixel_width *2 + 1) - cube_width;

    cubes[0].x = cube_left;
    cubes[0].y = cube_top;
    cubes[0].w = cube_width;
    cubes[0].h = cube_width;

    cubes[1].x = cube_left;
    cubes[1].y = cube_bottom;
    cubes[1].w = cube_width;
    cubes[1].h = cube_width;

    cubes[2].x = cube_right;
    cubes[2].y = cube_bottom;
    cubes[2].w = cube_width;
    cubes[2].h = cube_width;

    cubes[3].x = cube_right;
    cubes[3].y = cube_top;
    cubes[3].w = cube_width;
    cubes[3].h = cube_width;;

    float pillar_left = cube_left + pixel_width;
    float pillar_top = cube_top + cube_width + pixel_width;
    float pillar_right = cube_right + pixel_width;
    float pillar_bottom = cube_bottom - pixel_width;
    float pillar_width = border_width - pixel_width * 13;
    float pillar_height = border_height - pixel_width * 13;

    pillars[0].x = pillar_left;
    pillars[0].y = pillar_top;
    pillars[0].w = pixel_width;
    pillars[0].h = pillar_height;

    pillars[1].x = pillar_left + cube_width;
    pillars[1].y = pillar_bottom + pixel_width * 2;
    pillars[1].w = pillar_width;
    pillars[1].h = pixel_width;

    pillars[2].x = pillar_right;
    pillars[2].y = pillar_top;
    pillars[2].w = pixel_width;
    pillars[2].h = pillar_height;

    pillars[3].x = pillar_left + cube_width;
    pillars[3].y = pillar_top - cube_width;
    pillars[3].w = pillar_width;
    pillars[3].h = pixel_width;
  }
  ~Border() {

  }

  void render(SDL_Renderer *renderer) override {

    set_render_colour(renderer, BLACK);
    SDL_RenderFillRect(renderer, &border_outer);
    set_render_colour(renderer, WHITE);
    SDL_RenderFillRect(renderer, &background);
    set_render_colour(renderer, BLACK);
    for (SDL_FRect &i : cubes) {
      SDL_RenderFillRect(renderer, &i);
    }
      //SDL_RenderFillRect(renderer, &pillars[0]);
    for (SDL_FRect &i : pillars) {
      SDL_RenderFillRect(renderer, &i);
    }
    SDL_RenderFillRect(renderer, &border_inner);
  }

  float border_width;
  float border_height;
  float pixel_width;
  float cube_width;
  float inner_margin;
  float total_pixels;
  float left_x;
  float top_y;
  SDL_FRect border_outer;
  SDL_FRect border_inner;
  SDL_FRect background;
  SDL_FRect cubes[4];
  SDL_FRect pillars[4];
};
