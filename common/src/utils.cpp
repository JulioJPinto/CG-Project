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

std::vector<Point> parseOBJfile(std::string filename, std::string type) {
  std::vector<Point> points;
  std::vector<Point> sorted_points;
  std::ifstream file(filename);

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string type;
    iss >> type;
    if (type == "v") {
      Point point;
      iss >> point.x >> point.y >> point.z;
      points.push_back(point);
    } else if (type == "f") {
      std::string vertex;
      std::vector<int> vertex_indices;
      while (iss >> vertex) {
        std::string index = vertex.substr(0, vertex.find("/"));
        vertex_indices.push_back(std::stoi(index) - 1);
      }
      for (int i = 0; i < vertex_indices.size(); i++) {
        sorted_points.push_back(points[vertex_indices[i]]);
      }
    }
  }
  file.close();

  return sorted_points;
}

std::vector<Point> parse3Dfile(std::string filename) {
  std::vector<Point> points;
  std::ifstream file(filename);

  Point point;
  while (file >> point.x >> point.y >> point.z) {
    points.push_back(point);
  }

  file.close();

  return points;
}