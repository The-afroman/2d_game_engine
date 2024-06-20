
#ifndef KEYBOARDMOVEMENTSYSTEM_H
#define KEYBOARDMOVEMENTSYSTEM_H

#include <cmath>
#include <string>

#include "../Components/keyboard_controlled_component.h"
#include "../Components/projectile_emitter_component.h"
#include "../Components/rigid_body_component.h"
#include "../Components/sprite_component.h"
#include "../ECS/ecs.h"
#include "../Events/event_bus.h"
#include "../Events/keyboard_event.h"
#include "../Logger/logger.h"

class KeyboardMovementSystem : public System {
 public:
  KeyboardMovementSystem() {
    requireComponent<KeyboardControlledComponent>();
    requireComponent<SpriteComponent>();
    requireComponent<RigidBodyComponent>();
  }

  void update() {}
  void subscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
    // clang-format off
    eventBus->subscribe<KeyboardEvent>(this, &KeyboardMovementSystem::onKeypress);
  }
  // clang-format on
  void onKeypress(KeyboardEvent& event) {
    // change velocity of controlled sprite entity
    for (auto entity : getEntities()) {
      auto& kbControlComp = entity.getComponent<KeyboardControlledComponent>();
      auto& spriteComp = entity.getComponent<SpriteComponent>();
      auto& rigidBodyComp = entity.getComponent<RigidBodyComponent>();
      double projVelN = 0;
      if (entity.hasComponent<ProjectileEmitterComponent>()) {
        auto& projComp = entity.getComponent<ProjectileEmitterComponent>();
        projVelN = abs(projComp.projectileVel.x) > 0 ? abs(projComp.projectileVel.x) : abs(projComp.projectileVel.y);
      }
      switch (event.key_pressed) {
        case SDLK_w:
          if (entity.hasComponent<ProjectileEmitterComponent>()) {
            entity.getComponent<ProjectileEmitterComponent>().projectileVel.x = 0;
            entity.getComponent<ProjectileEmitterComponent>().projectileVel.y = -projVelN;
          }
          rigidBodyComp.velocity = kbControlComp.upVel;
          spriteComp.srcRect.y = 0;
          break;
        case SDLK_d:
          if (entity.hasComponent<ProjectileEmitterComponent>()) {
            entity.getComponent<ProjectileEmitterComponent>().projectileVel.x = projVelN;
            entity.getComponent<ProjectileEmitterComponent>().projectileVel.y = 0;
          }
          rigidBodyComp.velocity = kbControlComp.rightVel;
          spriteComp.srcRect.y = spriteComp.height * 1;
          break;
        case SDLK_s:
          if (entity.hasComponent<ProjectileEmitterComponent>()) {
            entity.getComponent<ProjectileEmitterComponent>().projectileVel.x = 0;
            entity.getComponent<ProjectileEmitterComponent>().projectileVel.y = projVelN;
          }
          rigidBodyComp.velocity = kbControlComp.downVel;
          spriteComp.srcRect.y = spriteComp.height * 2;
          break;
        case SDLK_a:
          if (entity.hasComponent<ProjectileEmitterComponent>()) {
            entity.getComponent<ProjectileEmitterComponent>().projectileVel.x = -projVelN;
            entity.getComponent<ProjectileEmitterComponent>().projectileVel.y = 0;
          }
          rigidBodyComp.velocity = kbControlComp.leftVel;
          spriteComp.srcRect.y = spriteComp.height * 3;
          break;
      }
    }
    std::string k(1, event.key_pressed);
    std::string kCode = std::to_string(event.key_pressed);
    Logger::info("Keypress Event: CODE[" + kCode + "]");
  }
};

#endif