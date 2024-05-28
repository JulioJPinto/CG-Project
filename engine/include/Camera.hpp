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
       
  glm::mat4 getViewMatrix() const {
        return glm::lookAt(position, position + forward, up);
    }

    glm::mat4 getProjectionMatrix(float ratio) const {
        return glm::perspective(glm::radians(static_cast<float>(fov)), ratio, near, far);
    }

    glm::mat4 getViewProjectionMatrix(float ratio) const {
        return getProjectionMatrix(ratio) * getViewMatrix();
    }
};


#endif  // CAMERA_HPP