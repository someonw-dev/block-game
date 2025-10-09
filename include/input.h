#include <SDL3/SDL.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_timer.h>

class InputHandler {
public:
  InputHandler(SDL_Scancode key_value) {
    key = key_value;

  }
  ~InputHandler() {

  }

  // if this returns true that means you can move
  // should only return true if it is the first press
  // or if the delay time has passed and it is still pressed
  bool get_pressed(const bool* keys) {
    end = SDL_GetTicks();

    if (!keys[key]) {
      pressed = false;
    }

    // return true if it is the first press
    if (keys[key] && !pressed) {
      pressed = true;
      start_time = SDL_GetTicks();
      return true;
    }

    // return true if it is still pressed AND the delay time has passed
    if ((end > start_time + DELAY) && pressed) {
      return true;
    }

    return false;
  }

private:
  SDL_Scancode key;
  bool pressed = false;
  const int DELAY = 300;
  Uint64 start_time = SDL_GetTicks();
  Uint64 end = SDL_GetTicks();
};
