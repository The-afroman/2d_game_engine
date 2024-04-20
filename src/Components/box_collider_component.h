#ifndef BOXCOLLIDERCOMPONENT_H
#define BOXCOLLIDERCOMPONENT_H

#include <glm/glm.hpp>

struct BoxColliderComponent {
  double width;
  double height;
  glm::vec2 offset;
  bool isColliding;

  BoxColliderComponent(double width = 0.0, double height = 0.0,
                       glm::vec2 offset = {0.0, 0.0}) {
    this->width = width;
    this->height = height;
    this->offset = offset;
    this->isColliding = false;
  }
};

#endif