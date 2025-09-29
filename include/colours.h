#pragma once

#include <SDL3/SDL_render.h>

enum Colours {
  RED,
  BLUE,
  GREEN,
  GRAY,
  DARK_RED,
  DARK_BLUE,
  DARK_GREEN,
  BLACK
};

void set_render_colour(SDL_Renderer *renderer, Colours colour);
