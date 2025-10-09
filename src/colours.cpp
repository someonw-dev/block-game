#include "../include/colours.h"
#include <SDL3/SDL_blendmode.h>
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
    case PURPLE: {
      SDL_SetRenderDrawColor(renderer, 191, 64, 191, 255);
      break;
    }
    case YELLOW: {
      SDL_SetRenderDrawColor(renderer, 255, 234, 0, 255);
      break;
    }
    case AQUA: {
      SDL_SetRenderDrawColor(renderer, 51, 255, 255, 255);
      break;
    }
    case ORANGE: {
      SDL_SetRenderDrawColor(renderer, 255, 95, 31, 255);
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
    case DARK_PURPLE: {
      SDL_SetRenderDrawColor(renderer, 112, 41, 99, 255);
      break;
    }
    case DARK_YELLOW: {
      SDL_SetRenderDrawColor(renderer, 228, 155, 15, 255);
      break;
    }
    case DARK_AQUA: {
      SDL_SetRenderDrawColor(renderer, 0, 115, 115, 255);
      break;
    }
    case DARK_ORANGE: {
      SDL_SetRenderDrawColor(renderer, 160, 82, 45, 255);
      break;
    }
    case BLACK: {
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      break;
    }
    case INVISIBLE: {
      SDL_SetRenderDrawColor(renderer, 200, 50, 50, 0);
      break;
    }
    case LIGHT_GRAY: {
      SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
      break;
    }
    case WHITE: {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      break;
    }
  }
}
