#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <string>
#include <vector>

#include "Camera.hpp"
#include "Configuration.hpp"
#include "Window.hpp"

class Configuration {
 public:
  Window window;
  Camera camera;
  std::vector<std::string> models;

  Configuration(Window window, Camera camera, std::vector<std::string> models);

  std::string toString();
};

#endif  // CONFIGURATION_HPP