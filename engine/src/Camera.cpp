#include "Camera.hpp"

#include <sstream>
#include <string>

Camera::Camera() {
  this->position = glm::vec3();
  this->lookAt = glm::vec3();
  this->up = glm::vec3();
  this->fov = 0;
  this->near = 0;
  this->far = 0;

}

Camera::Camera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 up, int fov, float near,
               float far) {
  this->position = position;
  this->lookAt = lookAt;
  this->up = up;

  glm::vec3 direction = glm::normalize(position - lookAt);
  this->right = glm::normalize(glm::cross(up, direction));
  this->real_up = glm::normalize(glm::cross(direction, right));
  this->forward = glm::normalize(lookAt - position);

  this->fov = fov;
  this->near = near;
  this->far = far;
}


Camera::Camera(const Camera& other) {
  // Copy member variables from 'other' to the current object
  this->position = other.position;
  this->lookAt = other.lookAt;
  this->up = other.up;
  this->fov = other.fov;
  this->near = other.near;
  this->far = other.far;
}
