#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../ECS/ecs.h"

class MovementSystem : public System {
public:
  MovementSystem() {
    // TODO: RequireComponent<TransformComponent>();
    //  ...
  }

  void Update() {
    // TODO:
    // Loop through all entities the system is interested in
    for (auto entity : getEntities()) {
      // TODO:
      // Loop through all entities
      // Update entity position
    }
  }
};

#endif