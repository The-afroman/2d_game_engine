#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include <SDL2/SDL.h>

#include <glm/fwd.hpp>

#include "../Components/camera_component.h"
#include "../Components/sprite_component.h"
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
      glm::vec2 transformCenter = transformComp.pos;
      if (entity.hasComponent<SpriteComponent>()) {
        transformCenter.x += entity.getComponent<SpriteComponent>().width / 2.0;
        transformCenter.y += entity.getComponent<SpriteComponent>().height / 2.0;
      }
      Logger::info("player: " + std::to_string(transformCenter.x) + " " + std::to_string(transformComp.pos.y));
      Logger::info("camera: " + std::to_string(camera.x) + " " + std::to_string(camera.y));
      if (transformCenter.x - (camera.w / 2.0) > 0 && (camera.w / 2.0) + transformComp.pos.x < Game::mapW) {
        camera.x = transformCenter.x - (camera.w / 2.0);
      }
      if (transformCenter.y - (camera.h / 2.0) > 0 && (camera.h / 2.0) + transformComp.pos.y < Game::mapH) {
        camera.y = transformCenter.y - (camera.h / 2.0);
      }

      camera.x = camera.x < 0 ? 0 : camera.x;
      camera.y = camera.y < 0 ? 0 : camera.y;
      // clang-format off
      camera.x = camera.x > Game::mapW - camera.w ? Game::mapW - camera.w : camera.x;
      camera.y = camera.y > Game::mapH - camera.h ? Game::mapH - camera.h : camera.y;
    }
  }
};

#endif