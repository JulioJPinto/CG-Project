#include "Camera.hpp"

#include <sstream>
#include <string>

Camera::Camera() {
  this->position = Point();
  this->lookAt = Point();
  this->up = Point();
  this->fov = 0;
  this->near = 0;
  this->far = 0;
}

Camera::Camera(Point position, Point lookAt, Point up, int fov, float near,
               float far) {
  this->position = position;
  this->lookAt = lookAt;
  this->up = up;
  this->fov = fov;
  this->near = near;
  this->far = far;
}

void Camera::changeVectors(Point position, Point lookAt, Point up) {
  this->position = position;
  this->lookAt = lookAt;
  this->up = up;
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
