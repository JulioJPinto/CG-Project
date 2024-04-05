#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>

#include "Window.hpp"

class Window {
 public:
  int width;
  int height;

  Window();
  Window(int width, int height);

  std::string toString();
};

#endif  // WINDOW_HPP