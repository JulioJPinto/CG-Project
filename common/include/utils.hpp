#ifndef UTILS_HPP
#define UTILS_HPP

#include <cmath>
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

  std::string toString();
  Point multiply(float value);

  bool operator==(const Point& other) const {
    return x == other.x && y == other.y && z == other.z;
  }

  auto normalize() {
    float norm = sqrt(x * x + y * y + z * z);
    return Point(x / norm, y / norm, z / norm);
  }

  auto cross(const Point& other) {
    return Point(y * other.z - z * other.y, z * other.x - x * other.z,
                 x * other.y - y * other.x);
  }

} Point;

struct Point2D {
  float x;
  float y;

  Point2D(float x_val = 0.0f, float y_val = 0.0f) : x(x_val), y(y_val) {}
};

struct PointHash {
  size_t operator()(const Point& p) const {
    return std::hash<float>()(p.x) ^ std::hash<float>()(p.y) ^
           std::hash<float>()(p.z);
  }
};

// Function to convert Point to string
std::vector<Point> parseFile(std::string filename);
void saveToFile(const std::vector<Point>& points, const char* filepath);

// Function to parse OBJ file
std::vector<Point> parseOBJfile(std::string filename);

// Function to parse 3D file
std::vector<Point> parse3Dfile(std::string filename);

#endif  // UTILS_HPP
