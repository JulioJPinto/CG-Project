#include "light.hpp"

#include <iostream>

Light createDirectionLight(glm::vec4 direction) {
  Light light;
  light.type = DIRECTIONAL;
  light.direction = direction;
  return light;
}

Light createPointLight(glm::vec4 position) {
  Light light;
  light.type = POINT;
  light.position = position;
  return light;
}

Light createSpotLight(glm::vec4 position, glm::vec4 direction, float cutoff) {
  Light light;
  light.type = SPOT;
  light.position = position;
  light.direction = direction;
  light.cutoff = cutoff;
  return light;
}

Material createMaterial(glm::vec4 ambient, glm::vec4 diffuse,
                        glm::vec4 specular, glm::vec4 emission,
                        float shininess) {
  Material material;
  material.ambient = ambient;
  material.diffuse = diffuse;
  material.specular = specular;
  material.emission = emission;
  material.shininess = shininess;
  return material;
}

void setupMaterial(Material m) {
  glMaterialfv(GL_FRONT, GL_AMBIENT, glm::value_ptr(m.ambient));
  glMaterialfv(GL_FRONT, GL_DIFFUSE, glm::value_ptr(m.diffuse));
  glMaterialfv(GL_FRONT, GL_SPECULAR, glm::value_ptr(m.specular));
  glMaterialfv(GL_FRONT, GL_EMISSION, glm::value_ptr(m.emission));
  glMaterialf(GL_FRONT, GL_SHININESS, m.shininess);
}

void setupLights(std::vector<Light> lights) {
  for (int i = 0; i < lights.size() && lights.size() < 8; i++) {
    Light light = lights[i];

    switch (light.type) {
      case DIRECTIONAL:
        glLightfv(GL_LIGHT0 + i, GL_POSITION, glm::value_ptr(light.direction));
        break;
      case POINT:
        glLightfv(GL_LIGHT0 + i, GL_POSITION, glm::value_ptr(light.position));
        break;
      case SPOT:
        glLightfv(GL_LIGHT0 + i, GL_POSITION, glm::value_ptr(light.position));
        glLightfv(GL_LIGHT0 + i, GL_SPOT_DIRECTION,
                  glm::value_ptr(light.direction));
        glLightf(GL_LIGHT0 + i, GL_SPOT_CUTOFF, light.cutoff);
        break;
    }
  }
}
