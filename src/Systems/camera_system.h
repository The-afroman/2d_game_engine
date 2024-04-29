#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include <SDL2/SDL.h>

#include "../Components/camera_component.h"
#include "../Components/transform_component.h"
#include "../ECS/ecs.h"
#include "../Game/game.h"
#include "../Logger/logger.h"

class CameraSystem : public System {
 public:
  CameraSystem() {
    requireComponent<CameraComponent>();
    requireComponent<TransformComponent>();
  }

  void update(SDL_Rect& camera) {
    for (auto entity : getEntities()) {
      auto& transformComp = entity.getComponent<TransformComponent>();
      if (transformComp.pos.x - camera.w / 2 > 0 &&
          camera.w / 2 + transformComp.pos.x < Game::mapW) {
        camera.x = transformComp.pos.x - camera.w / 2;
      }
      if (transformComp.pos.y - camera.h / 2 > 0 &&
          camera.h / 2 + transformComp.pos.y < Game::mapH) {
        camera.y = transformComp.pos.y - camera.h / 2;
      }

      camera.x = camera.x < 0 ? 0 : camera.x;
      camera.y = camera.y < 0 ? 0 : camera.y;
      camera.x = camera.x > camera.w ? camera.w : camera.x;
      camera.y = camera.y > camera.h ? camera.h : camera.y;
    }
  }
};

#endif