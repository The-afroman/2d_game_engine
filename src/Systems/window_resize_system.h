
#ifndef WINDOWRESIZESYSTEM_H
#define WINDOWRESIZESYSTEM_H

#include <SDL2/SDL.h>

#include "../Components/camera_component.h"
#include "../Components/transform_component.h"
#include "../ECS/ecs.h"
#include "../Events/window_resize_event.h"
#include "../Game/game.h"
#include "../Logger/logger.h"

class WindowResizeSystem : public System {
 public:
  WindowResizeSystem() {}

  void update() {}

  void subscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
    eventBus->subscribe<WindowResizeEvent>(this, &WindowResizeSystem::onResize);
  }

  void onResize(WindowResizeEvent& event) {
    event.camera->w = event.windowW;
    event.camera->h = event.windowH;
  }
};

#endif