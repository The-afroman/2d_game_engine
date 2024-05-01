#include "ecs.h"

#include <algorithm>
#include <vector>

#include "../Logger/logger.h"

int IComponent::nextID = 0;

int Entity::getID() const { return id; }

void Entity::kill() { registry->removeEntity(*this); }

void System::addEntity(Entity entity) { entities.push_back(entity); }

void System::removeEntity(Entity entity) {
  entities.erase(std::remove_if(entities.begin(), entities.end(), [&entity](Entity &other) { return entity == other; }),
                 entities.end());
}

std::vector<Entity> System::getEntities() const { return entities; }

const Signature &System::getComponentSig() const { return component_signature; }

Entity Registry::createEntity() {
  int entity_id;
  if (freeIds.empty()) {
    entity_id = numEntities++;
    // resize if needed
    if (std::size_t(entity_id) >= entityComponentSignatures.size()) {
      entityComponentSignatures.resize(entity_id + 1);
    }
  } else {
    entity_id = freeIds.front();
    freeIds.pop_front();
  }

  Entity entity(entity_id);
  entity.registry = this;
  entitiesToAdd.insert(entity);
  Logger::info("Entity created - id = " + std::to_string(entity_id));
  return entity;
}

void Registry::removeEntity(Entity entity) { entitiesToRemove.insert(entity); }

void Registry::update() {
  // TODO: remove entities which are in entitiesToRemove
  for (auto entity : entitiesToAdd) {
    addEntityToSystems(entity);
  }
  for (auto entity : entitiesToRemove) {
    removeEntityFromSystems(entity);
    // make the removed entity id available
    freeIds.push_back(entity.getID());
  }
  entitiesToAdd.clear();
  entitiesToRemove.clear();
}

void Registry::addEntityToSystems(Entity entity) {
  const auto entityId = entity.getID();
  const auto entityCompSig = entityComponentSignatures[entityId];

  for (auto &system : systems) {
    const auto &systemCompSig = system.second->getComponentSig();

    // check if entity has components required by system
    if ((systemCompSig & entityCompSig) == systemCompSig) {
      system.second->addEntity(entity);
    }
  }
}

void Registry::removeEntityFromSystems(Entity entity) {
  const auto entityId = entity.getID();
  const auto entityCompSig = entityComponentSignatures[entityId];

  for (auto &system : systems) {
    const auto &systemCompSig = system.second->getComponentSig();

    // check if entity has components required by system
    if ((systemCompSig & entityCompSig) == systemCompSig) {
      system.second->removeEntity(entity);
    }
  }
  // reset the component signature for the removed entity
  entityComponentSignatures[entityId].reset();
}