#include "Configuration.hpp"

#include <sstream>
#include <string>

Configuration::Configuration(const Window &window, const Camera &camera,
                             const Group &group) {
  this->window = window;
  this->camera = camera;
  this->group = group;
}
