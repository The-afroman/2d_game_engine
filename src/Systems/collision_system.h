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
        auto transformI = i->getComponent<TransformComponent>();
        auto transformJ = j->getComponent<TransformComponent>();
        auto colliderI = i->getComponent<BoxColliderComponent>();
        auto colliderJ = j->getComponent<BoxColliderComponent>();
        if (isAABBCollision(transformI.pos.x + colliderI.offset.x,
                            transformI.pos.y + colliderI.offset.y,
                            colliderI.width, colliderI.height, transformJ.pos.x,
                            transformJ.pos.y, colliderJ.width,
                            colliderJ.height)) {
          Logger::info("Collision of Entities: " + std::to_string(i->getID()) +
                       ", " + std::to_string(j->getID()));
          i->getComponent<BoxColliderComponent>().isColliding = true;
          j->getComponent<BoxColliderComponent>().isColliding = true;
        } else {
          i->getComponent<BoxColliderComponent>().isColliding = false;
          j->getComponent<BoxColliderComponent>().isColliding = false;
        }
      }
    }
  }
};

#endif