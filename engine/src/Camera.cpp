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
  this->type = FPS;
}

Camera::Camera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 up, int fov, float near,
               float far) {
  this->position = position;
  this->lookAt = lookAt;
  this->up = up;

  glm::vec3 direction = glm::normalize(position - lookAt);
  this->right = glm::normalize(glm::cross(up, direction));
  this->real_up = glm::normalize(glm::cross(direction, right));

  this->fov = fov;
  this->near = near;
  this->far = far;

  this->type = FPS;
}

glm::vec3 spherical2Cartesian(float theta, float phi, float r) {
  float x = r * sin(theta) * cos(phi);
  float y = r * sin(theta) * sin(phi);
  float z = r * cos(theta);
  return glm::vec3(x, y, z);
}

glm::vec3 cartesian2Spherical(glm::vec3 cartesian) {
  float r = glm::length(cartesian);
  float theta = acos(cartesian.z / r);
  float phi = atan(cartesian.y / cartesian.x);
  return glm::vec3(theta, phi, r);
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

void Camera::backwardMovementFPS() {
  glm::vec3 direction = glm::normalize(lookAt - position);
  position += direction;
  lookAt += direction;
}

void Camera::backwardMovementOrbital() {
  glm::vec3 direction = glm::normalize(lookAt - position);
  position += direction;
}

void Camera::backwardMovement() {
  if(type == FPS) {
    backwardMovementFPS();
  } else {
    backwardMovementOrbital();
  }
}

void Camera::forwardMovementFPS() {
  glm::vec3 direction = glm::normalize(lookAt - position);
  position -= direction;
  lookAt -= direction;
}

void Camera::forwardMovementOrbital() {
  glm::vec3 direction = glm::normalize(lookAt - position);
  position -= direction;
}

void Camera::forwardMovement() {
  if(type == FPS) {
    forwardMovementFPS();
  } else {
    forwardMovementOrbital();
  }
}

void Camera::leftMovementFPS() {
  glm::vec3 direction = glm::normalize(lookAt - position);
  glm::vec3 right = glm::normalize(glm::cross(up, direction));
  position -= right;
  lookAt -= right;
}

void Camera::leftMovementOrbital() {
  glm::vec3 direction = glm::normalize(lookAt - position);
  glm::vec3 right = glm::normalize(glm::cross(up, direction));
  lookAt -= right;
}

void Camera::leftMovement() {
  if(type == FPS) {
    leftMovementFPS();
  } else {
    leftMovementOrbital();
  }
}

void Camera::rightMovementFPS() {
  glm::vec3 direction = glm::normalize(lookAt - position);
  glm::vec3 right = glm::normalize(glm::cross(up, direction));
  position += right;
  lookAt += right;
}

void Camera::rightMovementOrbital() {
  glm::vec3 direction = glm::normalize(lookAt - position);
  glm::vec3 right = glm::normalize(glm::cross(up, direction));
  lookAt += right;
}

void Camera::rightMovement() {
  if(type == FPS) {
    rightMovementFPS();
  } else {
    rightMovementOrbital();
  }
}

void Camera::upMovementFPS() {
  glm::vec3 direction = glm::normalize(lookAt - position);
  glm::vec3 right = glm::normalize(glm::cross(up, direction));
  glm::vec3 up = glm::normalize(glm::cross(direction, right));
  position += up;
  lookAt += up;
}

void Camera::upMovementOrbital() {
  glm::vec3 direction = glm::normalize(lookAt - position);
  glm::vec3 right = glm::normalize(glm::cross(up, direction));
  glm::vec3 up = glm::normalize(glm::cross(direction, right));
  lookAt += up;
}

void Camera::upMovement() {
  if(type == FPS) {
    upMovementFPS();
  } else {
    upMovementOrbital();
  }
}

void Camera::downMovementFPS() {
  glm::vec3 direction = glm::normalize(lookAt - position);
  glm::vec3 right = glm::normalize(glm::cross(up, direction));
  glm::vec3 up = glm::normalize(glm::cross(direction, right));
  position -= up;
  lookAt -= up;
}

void Camera::downMovementOrbital() {
  glm::vec3 direction = glm::normalize(lookAt - position);
  glm::vec3 right = glm::normalize(glm::cross(up, direction));
  glm::vec3 up = glm::normalize(glm::cross(direction, right));
  lookAt -= up;
}

void Camera::downMovement() {
  if(type == FPS) {
    downMovementFPS();
  } else {
    downMovementOrbital();
    
  }
}


