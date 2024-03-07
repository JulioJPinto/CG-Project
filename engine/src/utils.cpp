#include "utils.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<Point> parseFile(std::string filename) {
  std::ifstream file(filename);
  std::vector<Point> points;

  if (!file.is_open()) {
    std::cerr << "Error: Unable to open file " << filename << std::endl;
    return points;
  }

  printf("filename: %s\n", filename.c_str());
  if (filename.find(".obj") != std::string::npos) {
    points = parseOBJfile(filename, "obj");
  } else if (filename.find(".3d") != std::string::npos) {
    points = parse3Dfile(filename);
  } else {
    std::cerr << "Error: File format not supported" << std::endl;
  }

  file.close();

  return points;
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