#include "Window.hpp"

#include <sstream>
#include <string>

Window::Window() {
  this->width = 0;
  this->height = 0;
}

Window::Window(float width, float height) {
  this->width = width;
  this->height = height;
}

std::string Window::toString() {
  std::stringstream ss;
  ss << "\tWidth: " << width << std::endl
     << "\tHeight: " << height << std::endl;
  return ss.str();
}
