#include "Camera.hpp"

#include <string>
#include <sstream>

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

std::string Camera::toString() {
  std::stringstream ss;
  ss << "\tPosition: " << position.toString() << std::endl
     << "\tLookAt: " << lookAt.toString() << std::endl
     << "\tUp: " << up.toString() << std::endl
     << "\tFOV: " << std::to_string(fov).c_str() << std::endl
     << "\tNear: " << std::to_string(near).c_str() << std::endl
     << "\tFar: " << std::to_string(far).c_str() << std::endl;
  return ss.str();
}
