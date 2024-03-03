#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <vector>

#include "Camera.hpp"
#include "Configuration.hpp"
#include "Window.hpp"

class Configuration {
 public:
  Window window;
  Camera camera;
  std::vector<char*> models;

  Configuration(Window window, Camera camera, std::vector<char*> models);
};

#endif  // CONFIGURATION_HPP