#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.hpp"
#include "utils.hpp"


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

  Camera();
  Camera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 up, int fov, float near,
         float far);

  Camera(const Camera& other);

  void leftMovement();
  void rightMovement();
  void forwardMovement();
  void backwardMovement();
  void spinUp();
  void spinDown();
  void spinLeft();
  void spinRight();

  //   std::string toString();
};

glm::vec3 spherical2Cartesian(float theta, float phi, float r);

glm::vec3 cartesian2Spherical(glm::vec3 cartesian);

#endif  // CAMERA_HPP