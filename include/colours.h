#pragma once

#include <SDL3/SDL_render.h>

enum Colours {
  RED,
  BLUE,
  GREEN,
  PURPLE,
  YELLOW,
  ORANGE,
  AQUA,
  GRAY,
  DARK_RED,
  DARK_BLUE,
  DARK_GREEN,
  DARK_PURPLE,
  DARK_YELLOW,
  DARK_ORANGE,
  DARK_AQUA,
  BLACK,
  INVISIBLE,
  LIGHT_GRAY
};

void set_render_colour(SDL_Renderer *renderer, Colours colour);
