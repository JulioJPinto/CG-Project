#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>

#include "utils.hpp"
#include "Camera.hpp"

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

  Camera(const Camera& other);

  void changeVectors(Point position, Point lookAt, Point up);

  //   std::string toString();
};

#endif  // CAMERA_HPP