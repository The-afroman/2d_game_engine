#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "../Components/box_collider_component.h"
#include "../Components/transform_component.h"
#include "../ECS/ecs.h"
#include "../Logger/logger.h"

class CollisionSystem : public System {
public:
  CollisionSystem() {
    requireComponent<TransformComponent>();
    requireComponent<BoxColliderComponent>();
  }

  bool isAABBCollision(double aX, double aY, double aW, double aH, double bX,
                       double bY, double bW, double bH) {
    return aX < bX + bW && aX + aW > bX && aY < bY + bH && aY + aH > bY;
  }

  void update() {
    auto entities = getEntities();

    for (auto i = entities.begin(); i != entities.end(); i++) {
      for (auto j = i; j != entities.end(); j++) {
        // skip if comparing the same enitity
        if (*i == *j) {
          continue;
        }

        // check for collisions
        if (isAABBCollision(i->getComponent<TransformComponent>().pos.x,
                            i->getComponent<TransformComponent>().pos.y,
                            i->getComponent<BoxColliderComponent>().width,
                            i->getComponent<BoxColliderComponent>().height,
                            j->getComponent<TransformComponent>().pos.x,
                            j->getComponent<TransformComponent>().pos.y,
                            j->getComponent<BoxColliderComponent>().width,
                            j->getComponent<BoxColliderComponent>().height)) {
          Logger::info("Collision of Entities: " + std::to_string(i->getID()) +
                       ", " + std::to_string(j->getID()));
          i->getComponent<BoxColliderComponent>().hasCollided = true;
          j->getComponent<BoxColliderComponent>().hasCollided = true;
        }
      }
    }
  }
};

#endif