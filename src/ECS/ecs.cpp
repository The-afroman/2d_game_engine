#include "ecs.h"
#include "../Logger/logger.h"
#include <algorithm>
#include <vector>

int IComponent::nextID = 0;

int Entity::getID() const { return id; }

void System::addEntity(Entity entity) { entities.push_back(entity); }

void System::removeEntity(Entity entity) {
  entities.erase(
      std::remove_if(entities.begin(), entities.end(),
                     [&entity](Entity &other) { return entity == other; }),
      entities.end());
}

std::vector<Entity> System::getEntities() const { return entities; }

const Signature &System::getComponentSig() const { return component_signature; }

Entity Registry::createEntity() {
  int entity_id = numEntities++;
  if (std::size_t(entity_id) >= entityComponentSignatures.size()) {
    entityComponentSignatures.resize(entity_id + 1);
  }

  Entity entity(entity_id);
  entity.registry = this;
  entitiesToAdd.insert(entity);
  Logger::info("Entity created - id = " + std::to_string(entity_id));
  return entity;
}

void Registry::update() {
  // TODO: remove entities which are in entitiesToRemove
  for (auto entity : entitiesToAdd) {
    addEntityToSystems(entity);
  }
  entitiesToAdd.clear();
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