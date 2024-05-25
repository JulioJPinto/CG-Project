#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>
#include <glm/glm.hpp>
#include "Camera.hpp"
#include "utils.hpp"

enum CameraType { ORBITAL, FPS };

class Camera {
 public:
  glm::vec3 position;
  glm::vec3 lookAt;
  glm::vec3 up;
  glm::vec3 right;
  glm::vec3 real_up;
  int fov;
  float near;
  float far;
  CameraType type;

  Camera();
  Camera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 up, int fov, float near,
         float far);

  Camera(const Camera& other);

  void leftMovement();
  void rightMovement();
  void upMovement();
  void downMovement();
  void forwardMovement();
  void backwardMovement();

  //   std::string toString();
};

#endif  // CAMERA_HPP