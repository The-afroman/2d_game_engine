#ifndef PROJECTILESYSTEM_H
#define PROJECTILESYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include <algorithm>
#include <glm/fwd.hpp>
#include <memory>

#include "../Components/box_collider_component.h"
#include "../Components/projectile_emitter_component.h"
#include "../Components/rigid_body_component.h"
#include "../Components/sprite_component.h"
#include "../Components/transform_component.h"
#include "../ECS/ecs.h"
#include "../Logger/logger.h"

class ProjectileSystem : public System {
 public:
  ProjectileSystem() {
    requireComponent<ProjectileEmitterComponent>();
    requireComponent<TransformComponent>();
  }

  void update(std::unique_ptr<Registry>& registry) {
    for (auto entity : getEntities()) {
      auto& projectileComp = entity.getComponent<ProjectileEmitterComponent>();
      auto& transformComp = entity.getComponent<TransformComponent>();

      if (SDL_GetTicks() - projectileComp.lastEmissionTime > projectileComp.repeatFreq) {
        // add a new projectile to the registry
        glm::vec2 projPos = transformComp.pos;
        if (entity.hasComponent<SpriteComponent>()) {
          projPos.x += transformComp.scale.x * entity.getComponent<SpriteComponent>().width / 2.0;
          projPos.y += transformComp.scale.y * entity.getComponent<SpriteComponent>().height / 2.0;
        }
        Entity projectile = registry->createEntity();
        projectile.addComponent<TransformComponent>(projPos, glm::vec2(1.0, 1.0));
        projectile.addComponent<RigidBodyComponent>(projectileComp.projectileVel);
        projectile.addComponent<SpriteComponent>("bullet-image", 4, 4, 9);
        projectile.addComponent<BoxColliderComponent>(4, 4);

        // update emission time
        projectileComp.lastEmissionTime = SDL_GetTicks();
      }
    }
  }
};

#endif