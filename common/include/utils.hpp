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

  // std::string toString();
} Point;

// Function to convert Point to string
std::vector<Point> parseFile(std::string filename);
void saveToFile(const std::vector<Point>& points, const char* filepath);

// Function to parse OBJ file
std::vector<Point> parseOBJfile(std::string filename, std::string type);

// Function to parse 3D file
std::vector<Point> parse3Dfile(std::string filename);

#endif  // UTILS_HPP