#ifndef UTILS_HPP
#define UTILS_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "utils.hpp"

// Define Point struct
typedef struct Point {
  float x;
  float y;
  float z;

  // Constructor
  Point(float x_val = 0.0f, float y_val = 0.0f, float z_val = 0.0f)
      : x(x_val), y(y_val), z(z_val) {}

  std::string toString() {
    std::stringstream ss;
    ss << "Point(" << x << ", " << y << ", " << z << ")";
    return ss.str();
  }
} Point;

// Function to convert Point to string
std::vector<Point> parseFile(std::string filename);

#endif  // UTILS_HPP
