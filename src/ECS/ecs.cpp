#include "ecs.h"
#include "../Logger/logger.h"
#include <algorithm>
#include <vector>

int Entity::getID() const {
    return id;
}

void System::addEntity(Entity entity) {
    entities.push_back(entity);
}

void System::removeEntity(Entity entity) {
    entities.erase(std::remove_if(entities.begin(), entities.end(), [&entity](Entity& other) {
        return entity == other;
    }),entities.end());
}

std::vector<Entity> System::getEntities() const {
    return entities;
}

const Signature& System::getComponentSig() const {
    return component_signature;
}