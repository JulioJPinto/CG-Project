#include "Configuration.hpp"

#include <sstream>
#include <string>

Configuration::Configuration(const Window &window, const Camera &camera,
                             const Group &group) {
  this->window = window;
  this->camera = camera;
  this->group = group;
  this->lights = {};
}

Configuration::Configuration(const Window &window, const Camera &camera,
                             const Group &group,
                             const std::vector<Light> &lights) {
  this->window = window;
  this->camera = camera;
  this->group = group;
  this->lights = lights;
}

bool Configuration::addLight(const Light &light) {
  if (this->lights.size() > 8) {
    return false;
  }

  this->lights.push_back(light);
  return true;
}

bool Configuration::removeLight(int index) {
  if (index < 0 || index >= this->lights.size()) {
    return false;
  }

  this->lights.erase(this->lights.begin() + index);
  return true;
}
