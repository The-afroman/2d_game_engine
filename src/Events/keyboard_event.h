
#ifndef KEYBOARDEVENT_H
#define KEYBOARDEVENT_H

#include <SDL2/SDL.h>

#include <string>

#include "../ECS/ecs.h"
#include "event_bus.h"

class KeyboardEvent : public Event {
 public:
  SDL_Keycode key_pressed;
  KeyboardEvent(SDL_Keycode key_pressed) { this->key_pressed = key_pressed; };
};

#endif