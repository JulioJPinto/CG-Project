#ifndef UTILS_HPP
#define UTILS_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Define Point struct
struct Point {
  float x;
  float y;
  float z;

  // Constructor
  Point(float x_val = 0.0f, float y_val = 0.0f, float z_val = 0.0f)
      : x(x_val), y(y_val), z(z_val) {}

  std::string toString();
  Point multiply(float value);

  bool operator==(const Point &other) const {
    return x == other.x && y == other.y && z == other.z;
  }
};

struct PointHash {
  size_t operator()(const Point &p) const {
    return std::hash<float>()(p.x) ^ std::hash<float>()(p.y) ^
           std::hash<float>()(p.z);
  }
};

// Function to convert Point to string
std::vector<Point> parseFile(std::string filename);
void saveToFile(const std::vector<Point> &points, const char *filepath);

// Function to parse OBJ file
std::vector<Point> parseOBJfile(std::string filename);

// Function to parse 3D file
std::vector<Point> parse3Dfile(std::string filename);

#endif // UTILS_HPP
