#ifndef LIGHT_HPP
#define LIGHT_HPP

extern "C" {
#include <GL/gl.h>
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
}
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

enum LightType { DIRECTIONAL, POINT, SPOT };

typedef struct {
  LightType type;
  glm::vec4 position;
  glm::vec4 direction;
  float cutoff;
} Light;

Light createDirectionLight(glm::vec4 direction);

Light createPointLight(glm::vec4 position);

Light createSpotLight(glm::vec4 position, glm::vec4 direction, float cutoff);

void setupLights(std::vector<Light> lights);

typedef struct {
  glm::vec4 ambient;
  glm::vec4 diffuse;
  glm::vec4 specular;
  glm::vec4 emission;
  float shininess;
} Material;

Material createMaterial(glm::vec4 ambient, glm::vec4 diffuse,
                        glm::vec4 specular, glm::vec4 emission,
                        float shininess);

void setupMaterial(Material m);

#endif  // LIGHT_HPP
