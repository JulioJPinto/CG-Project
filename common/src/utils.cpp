#include "../include/utils.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define DIR "../models/"

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

void saveToFile(
    const std::vector<Point>& points,
    const char* filepath) {  // Changed parameter type to const char*

  std::string buf(DIR);
  buf.append(filepath);

  std::ofstream file(buf);

  if (file.is_open()) {
    for (const auto& point : points) {
      file << point.x << " " << point.y << " " << point.z << "\n";
    }
    file.close();
    std::cout << "File saved successfully.\n";
  } else {
    std::cerr << "Unable to open file: " << filepath << std::endl;
  }
}
