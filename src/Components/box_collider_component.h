#ifndef BOXCOLLIDERCOMPONENT_H
#define BOXCOLLIDERCOMPONENT_H

#include <glm/glm.hpp>

struct BoxColliderComponent {
  double width;
  double height;
  bool isColliding;

  BoxColliderComponent(double width = 0.0, double height = 0.0) {
    this->width = width;
    this->height = height;
    this->isColliding = false;
  }
};

#endif