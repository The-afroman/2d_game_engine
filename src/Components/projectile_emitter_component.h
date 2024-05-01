#ifndef PROJECTILEEMITTERCOMPONENT_H
#define PROJECTILEEMITTERCOMPONENT_H

#include <SDL2/SDL_stdinc.h>

#include <glm/glm.hpp>

#include "../ECS/ecs.h"

struct ProjectileEmitterComponent {
  glm::vec2 projectileVel;
  Uint32 repeatFreq;
  int projectileDuration;
  int hitPercentDamage;
  Uint32 lastEmissionTime;
  bool isFriendly;

  ProjectileEmitterComponent(glm::vec2 projectileVel = {0.0, 0.0}, int repeatFreq = 0, int projectileDuration = 10000,
                             int hitPercentDamage = 0, int lastEmissionTime = 0, bool isFriendly = false) {
    this->projectileVel = projectileVel;
    this->repeatFreq = repeatFreq;
    this->projectileDuration = projectileDuration;
    this->hitPercentDamage = hitPercentDamage;
    this->lastEmissionTime = lastEmissionTime;
    this->isFriendly = isFriendly;
  }
};

#endif