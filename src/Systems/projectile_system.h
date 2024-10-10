#ifndef PROJECTILESYSTEM_H
#define PROJECTILESYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include <algorithm>
#include <cmath>
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
    requireComponent<RigidBodyComponent>();
  }

  void update(std::unique_ptr<Registry>& registry) {
    for (auto entity : getEntities()) {
      auto& projectileComp = entity.getComponent<ProjectileEmitterComponent>();
      auto& transformComp = entity.getComponent<TransformComponent>();
      if (SDL_GetTicks() - projectileComp.lastEmissionTime > projectileComp.repeatFreq) {
        // add a new projectile to the registry
        glm::vec2 projPos = transformComp.pos;
        if (entity.hasComponent<SpriteComponent>()) {
          double halfW = transformComp.scale.x * entity.getComponent<SpriteComponent>().width / 2.0;
          double halfH = transformComp.scale.y * entity.getComponent<SpriteComponent>().height / 2.0;
          projPos.x += halfW;
          projPos.y += halfH;
          Uint32 offset = 5;
          if (projectileComp.projectileVel.x > 0) {
            projPos.x += (offset + halfW);
          } else if (projectileComp.projectileVel.x < 0) {
            projPos.x -= (offset + halfW);
          }

          if (projectileComp.projectileVel.y > 0) {
            projPos.y += (offset + halfH);
          } else if (projectileComp.projectileVel.y < 0) {
            projPos.y -= (offset + halfH);
          }
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
