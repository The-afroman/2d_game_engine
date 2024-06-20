#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <SDL2/SDL.h>

#include <algorithm>

#include "../AssetMgr/asset_mgr.h"
#include "../Components/sprite_component.h"
#include "../Components/transform_component.h"
#include "../ECS/ecs.h"
#include "../Logger/logger.h"

class RenderSystem : public System {
 public:
  RenderSystem() {
    requireComponent<TransformComponent>();
    requireComponent<SpriteComponent>();
  }

  void update(SDL_Renderer *renderer, std::unique_ptr<AssetMgr> &assetMgr, SDL_Rect &camera) {
    // Loop through all entities the system is interested in
    for (auto entity : getEntities()) {
      const auto transform = entity.getComponent<TransformComponent>();
      const auto sprite = entity.getComponent<SpriteComponent>();

      SDL_FRect dstRect = {transform.pos.x - camera.x, transform.pos.y - camera.y,
                           static_cast<float>(sprite.width * transform.scale.x),
                           static_cast<float>(sprite.height * transform.scale.y)};
      // clang-format off
      SDL_RenderCopyExF(renderer,
                        assetMgr->getTexture(sprite.assetId),
                        &sprite.srcRect,
                        &dstRect, transform.rotation,
                        NULL,
                        SDL_FLIP_NONE);
      // clang-format on
    }
  }

  void sortByZIdx() {
    std::sort(entities.begin(), entities.end(), [](Entity a, Entity b) {
      return a.getComponent<SpriteComponent>().zIndex < b.getComponent<SpriteComponent>().zIndex;
    });
  }
};

#endif