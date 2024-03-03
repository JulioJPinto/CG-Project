#include "Configuration.hpp"

Configuration::Configuration(Window window, Camera camera,
                             std::vector<char*> models) {
  this->window = window;
  this->camera = camera;
  this->models = models;
}
