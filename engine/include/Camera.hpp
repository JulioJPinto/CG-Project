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

  private:
    void backwardMovementFPS();
    void backwardMovementOrbital();
    void forwardMovementFPS();
    void forwardMovementOrbital();
    void leftMovementFPS();
    void leftMovementOrbital();
    void rightMovementFPS();
    void rightMovementOrbital();
    void upMovementFPS();
    void upMovementOrbital();
    void downMovementFPS();
    void downMovementOrbital();

  //   std::string toString();
};

glm::vec3 spherical2Cartesian(float theta, float phi, float r);

glm::vec3 cartesian2Spherical(glm::vec3 cartesian);

#endif  // CAMERA_HPP