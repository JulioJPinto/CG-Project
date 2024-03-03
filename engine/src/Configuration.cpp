#include "Configuration.hpp"

#include <string>
#include <sstream>

Configuration::Configuration(Window window, Camera camera,
                             std::vector<std::string> models) {
  this->window = window;
  this->camera = camera;
  this->models = models;
}

std::string vectorToString(std::vector<std::string> v) {
  std::stringstream ss;
  for (auto i : v) {
    ss << i << " ";
  }
  return ss.str();
}

std::string Configuration::toString() {
  std::stringstream ss;
  ss << "Window:\n" << window.toString() << std::endl
     << "Camera:\n" << camera.toString() << std::endl
     << "Models: " << vectorToString(models) << std::endl;
  return ss.str();
}
