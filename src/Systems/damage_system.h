
#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H

#include <string>

#include "../Components/box_collider_component.h"
#include "../ECS/ecs.h"
#include "../Events/collision_event.h"
#include "../Events/event_bus.h"
#include "../Logger/logger.h"

class DamageSystem : public System {
 public:
  DamageSystem() { requireComponent<BoxColliderComponent>(); }

  void subscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
    eventBus->subscribe<CollisionEvent>(this, &DamageSystem::onCollision);
  }

  void onCollision(CollisionEvent& event) {
    Logger::info("Collision occured with " + std::to_string(event.a.getID()) + " & " + std::to_string(event.b.getID()));
    event.a.kill();
    event.b.kill();
  }

  void update() {}
};

#endif