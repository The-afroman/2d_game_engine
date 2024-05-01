#ifndef KEYBOARDCONTROLLEDCOMPONENT_H
#define KEYBOARDCONTROLLEDCOMPONENT_H

#include <glm/glm.hpp>

struct KeyboardControlledComponent {
  glm::vec2 upVel;
  glm::vec2 downVel;
  glm::vec2 leftVel;
  glm::vec2 rightVel;

  KeyboardControlledComponent(glm::vec2 upVel = {0.0, 0.0}, glm::vec2 rightVel = {0.0, 0.0},
                              glm::vec2 downVel = {0.0, 0.0}, glm::vec2 leftVel = {0.0, 0.0}) {
    this->upVel = upVel;
    this->downVel = downVel;
    this->leftVel = leftVel;
    this->rightVel = rightVel;
  }
};

#endif