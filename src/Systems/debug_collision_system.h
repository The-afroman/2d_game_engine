#ifndef DEBUGCOLLISIONSYSTEM_H
#define DEBUGCOLLISIONSYSTEM_H

#include <SDL2/SDL.h>

#include "../Components/box_collider_component.h"
#include "../Components/transform_component.h"
#include "../ECS/ecs.h"
#include "../Logger/logger.h"

class DebugCollisionSystem : public System {
 public:
  DebugCollisionSystem() {
    requireComponent<TransformComponent>();
    requireComponent<BoxColliderComponent>();
  }

  void update(SDL_Renderer *renderer, SDL_Rect &camera, bool debugActive) {
    if (debugActive) {
      for (auto entity : getEntities()) {
        auto transform = entity.getComponent<TransformComponent>();
        auto collider = entity.getComponent<BoxColliderComponent>();
        SDL_FRect debugBox = {transform.pos.x + collider.offset.x - camera.x,
                              transform.pos.y + collider.offset.y - camera.y,
                              static_cast<float>(collider.width),
                              static_cast<float>(collider.height)};
        if (collider.isColliding) {
          SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        } else {
          SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        }
        SDL_RenderDrawRectF(renderer, &debugBox);
      }
    }
  }
};

#endif