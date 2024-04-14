#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "../Components/sprite_component.h"
#include "../Components/transform_component.h"
#include "../ECS/ecs.h"
#include "../Logger/logger.h"
#include <SDL2/SDL.h>

class RenderSystem : public System {
public:
  RenderSystem() {
    requireComponent<TransformComponent>();
    requireComponent<SpriteComponent>();
  }

  void update(SDL_Renderer *renderer, std::unique_ptr<AssetMgr> &assetMgr) {
    // TODO:
    // Loop through all entities the system is interested in
    for (auto entity : getEntities()) {
      const auto transform = entity.getComponent<TransformComponent>();
      const auto sprite = entity.getComponent<SpriteComponent>();

      SDL_Rect dstRect = {static_cast<int>(transform.pos.x),
                          static_cast<int>(transform.pos.y),
                          static_cast<int>(sprite.width * transform.scale.x),
                          static_cast<int>(sprite.height * transform.scale.y)};

      SDL_RenderCopyEx(renderer, assetMgr->getTexture(sprite.assetId),
                       &sprite.srcRect, &dstRect, transform.rotation, NULL,
                       SDL_FLIP_NONE);
    }
  }
};

#endif