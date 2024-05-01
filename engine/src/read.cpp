#include "read.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "model.hpp"

std::unordered_map<std::string, Model> hash_models;

Model read3DAdvancedFile(const char* filepath) {
  std::ifstream file(filepath);

  std::vector<Point> points;
  std::vector<Point> normals;
  std::vector<Point2D> textures;

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    char type;
    if (iss >> type) {
      switch (type) {
        case 'p': {
          float x, y, z;
          if (iss >> x >> y >> z) {
            points.push_back(Point(x, y, z));
          }
          break;
        }
        case 'n': {
          float x, y, z;
          if (iss >> x >> y >> z) {
            normals.push_back(Point(x, y, z));
          }
          break;
        }
        case 't': {
          float u, v;
          if (iss >> u >> v) {
            textures.push_back(Point2D(u, v));
          }
          break;
        }
        default:
          break;
      }
    }
  }

  Model model(filepath, points, normals, textures);
  hash_models[filepath] = model;

  return model;
}

Model read3DSimpleFile(const char* filepath) {
  std::ifstream file(filepath);

  std::vector<Point> points;

  Point point;
  while (file >> point.x >> point.y >> point.z) {
    points.push_back(point);
  }

  Model model(filepath, points);
  hash_models[filepath] = model;

  return model;
}

Model read3DFile(const char* filepath) {
  std::ifstream file(filepath);

  char type;
  if (file >> type) {
    if (type == '#') {
      return read3DAdvancedFile(filepath);
    } else {
      return read3DSimpleFile(filepath);
    }
  }
}

Model readFile(const char* filepath) {
  std::ifstream file(filepath);

  if (!file.is_open()) {
    std::cerr << "Error opening file" << std::endl;
    return Model();
  }

  if (hash_models.find(filepath) != hash_models.end()) {
    std::cout << filepath << " already read." << std::endl;
    return hash_models[filepath];
  }

  if (std::filesystem::path(filepath).extension() == ".3d") {
    return read3DFile(filepath);
  }

  return Model();
}
