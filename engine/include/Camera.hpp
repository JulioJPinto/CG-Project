#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Camera.hpp"
#include "utils.hpp"

class Camera {
 public:
  Point position;
  Point lookAt;
  Point up;
  int fov;
  float near;
  float far;

  Camera();
  Camera(Point position, Point lookAt, Point up, int fov, float near,
         float far);
};

#endif  // CAMERA_HPP