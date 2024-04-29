
#ifndef WINDOWRESIZEEVENT_H
#define WINDOWRESIZEEVENT_H

#include <SDL2/SDL.h>

#include <string>

#include "../ECS/ecs.h"
#include "event_bus.h"

class WindowResizeEvent : public Event {
 public:
  int windowW;
  int windowH;
  SDL_Rect* camera;
  WindowResizeEvent(int windowW, int windowH, SDL_Rect* camera)
      : windowW(windowW), windowH(windowH), camera(camera) {}
};

#endif