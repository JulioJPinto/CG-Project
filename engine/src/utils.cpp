#include "utils.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<Point> parseFile(std::string filename) {
  std::vector<Point> points;
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Error: Unable to open file " << filename << std::endl;
    return points;
  }

  Point point;
  while (file >> point.x >> point.y >> point.z) {
    points.push_back(point);
  }
  file.close();
  return points;
}