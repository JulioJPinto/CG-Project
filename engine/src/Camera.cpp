#include "utils.hpp"

class Camera {
 public:
  Point position;
  Point lookAt;
  Point up;
  int fov;
  float near;
  float far;

  Camera() {
    this->position = Point();
    this->lookAt = Point();
    this->up = Point();
    this->fov = 0;
    this->near = 0;
    this->far = 0;
  }

  Camera(Point position, Point lookAt, Point up, int fov, float near,
         float far) {
    this->position = position;
    this->lookAt = lookAt;
    this->up = up;
    this->fov = fov;
    this->near = near;
    this->far = far;
  }
};
