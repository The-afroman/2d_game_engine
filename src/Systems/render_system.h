#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "../Components/transform_component.h"
#include "../Components/sprite_component.h"
#include "../ECS/ecs.h"
#include "../Logger/logger.h"
#include <SDL2/SDL.h>

class RenderSystem : public System {
public:
  RenderSystem() {
    requireComponent<TransformComponent>();
    requireComponent<SpriteComponent>();
  }

  void update(SDL_Renderer* renderer) {
    // TODO:
    // Loop through all entities the system is interested in
    for (auto entity : getEntities()) {
      const auto transform = entity.getComponent<TransformComponent>();
      const auto sprite = entity.getComponent<SpriteComponent>();

      SDL_Rect rect = {
        static_cast<int>(transform.pos.x),
        static_cast<int>(transform.pos.y),
        sprite.width,
        sprite.height,
      };
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      SDL_RenderFillRect(renderer, &rect);
    }
  }
};

#endif