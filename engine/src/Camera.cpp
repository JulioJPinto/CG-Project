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

  this->fov = fov;
  this->near = near;
  this->far = far;
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

void Camera::leftMovement() {
  glm::vec3 direction = glm::normalize(lookAt - position);
  glm::vec3 right = glm::normalize(glm::cross(up, direction));
  position -= right;
  lookAt -= right;
}

void Camera::rightMovement() {
  glm::vec3 direction = glm::normalize(lookAt - position);
  glm::vec3 right = glm::normalize(glm::cross(up, direction));
  position += right;
  lookAt += right;
}

void Camera::forwardMovement() {
  glm::vec3 direction = glm::normalize(lookAt - position);
  position += direction;
  lookAt += direction;
}

void Camera::backwardMovement() {
  glm::vec3 direction = glm::normalize(lookAt - position);
  position -= direction;
  lookAt -= direction;
}

//in the spin functions what should alter is the position, they spin around the lookat point
void Camera::spinLeft() {
  glm::vec3 direction = glm::normalize(lookAt - position);
  glm::vec3 right = glm::normalize(glm::cross(up, direction));
  glm::vec3 new_position = cartesian2Spherical(position);
  new_position.y -= 0.1;
  new_position = spherical2Cartesian(new_position.x, new_position.y, new_position.z);

  position = new_position;
}

void Camera::spinRight() {
  glm::vec3 direction = glm::normalize(lookAt - position);
  glm::vec3 right = glm::normalize(glm::cross(up, direction));
  glm::vec3 new_position = cartesian2Spherical(position);
  new_position.y += 0.1;
  new_position = spherical2Cartesian(new_position.x, new_position.y, new_position.z);

  position = new_position;
}

void Camera::spinUp() {
  glm::vec3 direction = glm::normalize(lookAt - position);
  glm::vec3 right = glm::normalize(glm::cross(up, direction));
  glm::vec3 new_position = cartesian2Spherical(position);
  new_position.x += 0.1;
  new_position = spherical2Cartesian(new_position.x, new_position.y, new_position.z);

  position = new_position;
}

void Camera::spinDown() {
  glm::vec3 direction = glm::normalize(lookAt - position);
  glm::vec3 right = glm::normalize(glm::cross(up, direction));
  glm::vec3 new_position = cartesian2Spherical(position);
  new_position.x -= 0.1;
  new_position = spherical2Cartesian(new_position.x, new_position.y, new_position.z);

  position = new_position;
}
