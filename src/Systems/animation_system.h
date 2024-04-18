
#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include "../Components/animation_component.h"
#include "../Components/sprite_component.h"
#include "../ECS/ecs.h"
#include "../Logger/logger.h"
#include <SDL2/SDL.h>

class AnimationSystem : public System {
public:
  AnimationSystem() {
    requireComponent<SpriteComponent>();
    requireComponent<AnimationComponent>();
  }

  void update() {

    for (auto entity : getEntities()) {
      auto &animation = entity.getComponent<AnimationComponent>();
      auto &sprite = entity.getComponent<SpriteComponent>();
      animation.currentFrame = ((SDL_GetTicks() - animation.startTime) *
                                animation.frameRate / 1000) %
                               animation.numFrames;
      sprite.srcRect.x = animation.currentFrame * sprite.width;
    }
  }
};

#endif