#ifndef BOXCOLLIDERCOMPONENT_H
#define BOXCOLLIDERCOMPONENT_H

#include <glm/glm.hpp>

struct BoxColliderComponent {
  glm::vec2 pos;
  double width;
  double height;
  bool hasCollided;

  BoxColliderComponent(double width = 0.0, double height = 0.0) {
    this->width = width;
    this->height = height;
    this->hasCollided = false;
  }
};

#endif