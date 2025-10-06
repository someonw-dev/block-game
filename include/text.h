#pragma once

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include "object.h"
#include "fonts.h"

class Text : public Object {
public:
  Text(const char *output, float x, float y, float w, SDL_Renderer *renderer) : Object(x, y, 0, 0) {
    SDL_Color color = {0, 0, 0, SDL_ALPHA_OPAQUE};
    SDL_Color bg = {255, 255, 255, SDL_ALPHA_OPAQUE};

    ////text = TTF_RenderText_Shaded(fonts::default_font, output, 0, color, bg);
    text = TTF_RenderText_Blended(fonts::default_font, output, 0, color);
    if (text) {
      texture = SDL_CreateTextureFromSurface(renderer, text);
      SDL_DestroySurface(text);
    }

    float currentWidth;
    float currentHeight;

    SDL_GetTextureSize(texture, &currentWidth, &currentHeight);
    float ratio = w/currentWidth;
    region.w = w;
    region.h = currentHeight * ratio;
  }
  ~Text() {}

  void render(SDL_Renderer *renderer) override {
    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //SDL_RenderFillRect(renderer, &region);

    SDL_RenderTexture(renderer, texture, NULL, &region);
  }

private:
  SDL_Surface *text;
  SDL_Texture *texture = NULL;

};
