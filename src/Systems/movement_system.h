#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../Components/projectile_emitter_component.h"
#include "../Components/rigid_body_component.h"
#include "../Components/transform_component.h"
#include "../ECS/ecs.h"
#include "../Logger/logger.h"

class MovementSystem : public System {
 public:
  MovementSystem() {
    requireComponent<TransformComponent>();
    requireComponent<RigidBodyComponent>();
  }

  void update(double deltaTime) {
    // TODO:
    // Loop through all entities the system is interested in
    for (auto entity : getEntities()) {
      auto &transform = entity.getComponent<TransformComponent>();
      const auto rbody = entity.getComponent<RigidBodyComponent>();
      transform.pos.x += rbody.velocity.x * deltaTime;
      transform.pos.y += rbody.velocity.y * deltaTime;
    }
  }
};

#endif