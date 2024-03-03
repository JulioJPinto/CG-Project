#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include "Camera.hpp"
#include "Configuration.hpp"
#include "Window.hpp"

#include <vector>
#include <string>

class Configuration {
 public:
  Window window;
  Camera camera;
  std::vector<std::string> models;

  Configuration(Window window, Camera camera, std::vector<std::string> models);

  std::string toString();
};

#endif  // CONFIGURATION_HPP