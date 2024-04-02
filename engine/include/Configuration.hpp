#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <string>
#include <vector>

#include "Camera.hpp"
#include "Configuration.hpp"
#include "Window.hpp"
#include "group.hpp"

class Configuration {
 public:
  Window window;
  Camera camera;
  Group group;
  Configuration() = default;
  Configuration(const Window &window, const Camera &camera, const Group &group);
  // std::string toString();
};

#endif  // CONFIGURATION_HPP