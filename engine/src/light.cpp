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
  if (lights.size() != 0) {
    std::cout << "Setting up lights\n";
    float amb[4] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
    glEnable(GL_LIGHTING);
    for (int i = 0; i < lights.size(); i++) {
      float white[4] = {1.0, 1.0, 1.0, 1.0};

      glEnable(GL_LIGHT0 + i);
      glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, white);
      glLightfv(GL_LIGHT0 + i, GL_SPECULAR, white);
      std::cout << "Light " << i << std::endl;
    }
  }
}

void drawLights(std::vector<Light> lights) {
  for (int i = 0; i < lights.size() && lights.size() < 8; i++) {
    Light light = lights[i];

    switch (light.type) {
      case DIRECTIONAL: {
        float direction[4] = {light.direction.x, light.direction.y,
                              light.direction.z, 0.0f};
        glLightfv(GL_LIGHT0 + i, GL_POSITION, direction);
        break;
      }
      case POINT: {
        float position[4] = {light.position.x, light.position.y,
                             light.position.z, 1.0f};
        glLightfv(GL_LIGHT0 + i, GL_POSITION, position);
        break;
      }
      case SPOT: {
        float postion[4] = {light.position.x, light.position.y,
                            light.position.z, 1.0f};
        glLightfv(GL_LIGHT0 + i, GL_POSITION, postion);
        float direction[4] = {light.direction.x, light.direction.y,
                              light.direction.z, 0.0f};
        glLightfv(GL_LIGHT0 + i, GL_SPOT_DIRECTION, direction);
        glLightf(GL_LIGHT0 + i, GL_SPOT_CUTOFF, light.cutoff);
        break;
      }
    }
  }
}
