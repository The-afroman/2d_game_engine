#ifndef DEBUGCOLLISIONSYSTEM_H
#define DEBUGCOLLISIONSYSTEM_H

#include "../Components/box_collider_component.h"
#include "../Components/transform_component.h"
#include "../ECS/ecs.h"
#include "../Logger/logger.h"
#include <SDL2/SDL.h>

class DebugCollisionSystem : public System {
public:
  DebugCollisionSystem() {
    requireComponent<TransformComponent>();
    requireComponent<BoxColliderComponent>();
  }

  void update(SDL_Renderer *renderer, bool debugActive) {
    if (debugActive) {
      for (auto entity : getEntities()) {
        auto transformComp = entity.getComponent<TransformComponent>();
        auto boxColliderComp = entity.getComponent<BoxColliderComponent>();
        SDL_FRect debugBox = {transformComp.pos.x, transformComp.pos.y,
                              static_cast<float>(boxColliderComp.width),
                              static_cast<float>(boxColliderComp.height)};
        if (boxColliderComp.isColliding) {
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