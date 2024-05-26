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
  glm::vec3 forward;
  int fov;
  float near;
  float far;

  Camera();
  Camera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 up, int fov, float near,
         float far);

  Camera(const Camera& other);

  //   std::string toString();
};

#endif  // CAMERA_HPP