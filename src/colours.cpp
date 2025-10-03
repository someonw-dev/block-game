#include "../include/colours.h"
#include <SDL3/SDL_render.h>

void set_render_colour(SDL_Renderer *renderer, Colours colour) {
  switch (colour) {
    case RED: {
      SDL_SetRenderDrawColor(renderer, 244, 55, 66, 255);
      break;
    }
    case BLUE: {
      SDL_SetRenderDrawColor(renderer, 0, 80, 200, 255);
      break;
    }
    case GREEN: {
      SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
      break;
    }
    case GRAY: {
      SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
      break;
    }
    case DARK_RED: {
      SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);
      break;
    }
    case DARK_BLUE: {
      SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
      break;
    }
    case DARK_GREEN: {
      SDL_SetRenderDrawColor(renderer, 0, 130, 0, 255);
      break;
    }
    case BLACK: {
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      break;
    }
  }
}
