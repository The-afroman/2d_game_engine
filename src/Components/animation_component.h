#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <SDL2/SDL.h>

struct AnimationComponent {
  int numFrames;
  int currentFrame;
  int frameRate;
  bool loop;
  int startTime;

  AnimationComponent(int numFrames = 1, int frameRate = 1, bool loop = true) {
    this->numFrames = numFrames;
    this->currentFrame = 1;
    this->frameRate = frameRate;
    this->loop = loop;
    this->startTime = SDL_GetTicks();
  }
};

#endif